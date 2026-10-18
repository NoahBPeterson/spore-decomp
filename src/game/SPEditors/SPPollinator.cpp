// src/game/SPEditors/SPPollinator.cpp -- migrated from slice(s) s00612270, s006108a0, s0060f910, s0060ea40, s0060c780 by tools/migrate/rewrite.py
// Object file: SPEditors/SPPollinator.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Internet/HTTPMultipartRelatedPostBodyStream.h"
#include "EA/Messaging/IHandler.h"
#include "EA/Messaging/Server.h"
#include "EA/Audio/IPrimitive.h"
#include "EA/IO/IStream.h"
#include "EA/IO/MemoryStream.h"
#include "EA/Variant.h"
#include "EA/ArgScript/cCommandBase.h"
#include "SP/cJobResultMessage.h"
#include "SP/cPollinator.h"
#include "SP/cPollinatorCheat.h"
#include "cSPUILayout.h"
#include "SP/cString.h"
#include "EA/Audio/FactoryBinarySampleData.h"
#include "eastl/allocator.h"
#include "SP/FunctionalMatch/Constraint.h"
#include <string.h>

// unnamed retail callees and globals (address in the comment)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags, unsigned debugFlags,
                                          const char* file, int line);
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);  // E8 call (0x011e0744)
extern "C" unsigned int __cdecl strlen(const char*);
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
extern "C" long __cdecl _InterlockedExchangeAdd(long volatile*, long);
extern const char kJobResultMessageType[];  // 0x0164d214
#pragma intrinsic(strlen)
#pragma intrinsic(_InterlockedExchange)
#pragma intrinsic(_InterlockedExchangeAdd)

// ---- items of slice s0060c780 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void EASTL_allocator_deallocate(void* p); // 0x00f47380
extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags, unsigned debugFlags,
                                          const char* file, int line);
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);  // E8 call (0x011e0744)
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags, const char* file, int line);
void operator delete(void*);
inline void* operator new(unsigned int, void* p) { return p; }
#define PV(n) virtual void pv##n();
class IMessageListener {
 public:
  PV(0) PV(1)
};
class IMessageServer {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void MessageSend(uint32_t messageID, void* pData, void* pListener);  // +0x14
  virtual void MessagePost(uint32_t messageID, void* pData, int, int);  // +0x18
  PV(7) PV(8)
  virtual void AddListener(IMessageListener* pListener, uint32_t messageID);   // +0x24
  PV(10)
  virtual void RemoveListener(IMessageListener* pListener, uint32_t messageID, int priority);  // +0x2c
};
namespace SP {
IMessageServer* MessageServer();           // 0x0067dcc0
}
struct ResourceKey {
  uint32_t instanceID;
  uint32_t typeID;
  uint32_t groupID;
};
void operator delete(void* p, const char*);
extern "C" long __cdecl _InterlockedExchangeAdd(long volatile*, long);
namespace EA {
namespace IO {
class IStream_s0060_c780 {
 public:
  IStream_s0060_c780() {}
  virtual ~IStream_s0060_c780() {}
  virtual int AddRef();
  virtual int Release();
  virtual uint32_t GetType() const;
  virtual int GetAccessFlags() const;
  virtual int GetState() const;
  virtual bool Close();
  virtual uint32_t GetSize() const;       // +0x1c
  virtual bool SetSize(uint32_t size);
  virtual int GetPosition(int positionType) const;  // +0x24
  virtual bool SetPosition(int position, int positionType);  // +0x28
  virtual uint32_t GetAvailable() const;  // +0x2c
  virtual uint32_t Read(void* pData, uint32_t nSize);
  virtual bool Flush();
  virtual bool Write(const void* pData, uint32_t nSize);  // +0x38
};
}
}
namespace SP {
struct ResourceKey {
  uint32_t instanceID;
  uint32_t typeID;
  uint32_t groupID;
};
}
namespace SP {
struct UploadEntry {
  ResourceKey mKey;
  bool mbFlag0;  // +0xc
  bool mbFlag1;  // +0xd
  UploadEntry(const ResourceKey& key, bool bFlag0, bool bFlag1);
  UploadEntry(const UploadEntry& x) : mKey(x.mKey), mbFlag0(x.mbFlag0), mbFlag1(x.mbFlag1) {}
};
}
namespace SP {
uint32_t FNV1(const char* pName, uint32_t nInitial, int bLowerCase);  // 0x00932e80
}
namespace SP {
struct cAchievementSource {
  char pad[0x43c];
  int mnID;  // +0x43c
};
}
namespace SP {
class cPollinator_s0060_c780 {
 public:
  void SetEnabledState(int nState);  // 0x0060cec0 (SP::cPollinator::SetEnabledState)
  char pad[0xb0];
  bool mbShutdownInProgress;  // +0xb0
  char pad2[0x40];
  bool mbPollinationEnabled;  // +0xf1 (retail layout; +0xb1 in the 2008 PDB)
};
}
namespace SP {
struct cAchievementsController {
  void AutoTest(uint32_t nAchievementID, int);  // 0x00676e90
};
}
namespace SP {
cAchievementsController* GetAchievementsController();  // 0x00675250
}
namespace SP {
struct cGameEventMessage {
  uint32_t pad0;
  uint32_t mnEventID;  // +0x4
};
}
struct VariantHelper {
  uint64_t mUint64;       // +0x0
  uint32_t pad8[2];
  uint16_t mFlags;        // +0x10
  uint16_t mTypeId;       // +0x12
  VariantHelper& operator=(const uint64_t& value);
  void Destruct(int);                                                       // 0x0093db80
  void Assign(int typeId, int, const void* pValue, int nSize, int bCopy);   // 0x0093dd80
};
struct IListener {
  PV(0) PV(1) PV(2) PV(3)
  virtual int GetID();                                    // +0x10
  PV(5)
  virtual void Notify(int, int, void* pData);              // +0x18
  PV(7)
  virtual bool IsReady();                                  // +0x20
};
template <typename T>
struct DequeIterator {
  T* mpCurrent;
  T* mpBegin;
  T* mpEnd;
  T** mpCurrentArrayPtr;
  enum { kSubarraySize = 0x100 / sizeof(T) };
  DequeIterator& operator++() {
    ++mpCurrent;
    if (mpCurrent == mpEnd) {
      ++mpCurrentArrayPtr;
      mpBegin = *mpCurrentArrayPtr;
      mpEnd = mpBegin + kSubarraySize;
      mpCurrent = mpBegin;
    }
    return *this;
  }
  void SetSubarray(T** pArrayPtr) {
    mpCurrentArrayPtr = pArrayPtr;
    mpBegin = *pArrayPtr;
    mpEnd = mpBegin + kSubarraySize;
  }
};
typedef DequeIterator<IListener*> ListenerIterator;
struct ListenerQuery {
  int mnID;
  void* mpData;
};
namespace StreamDeque {
using EA::IO::IStream_s0060_c780;
}
namespace StreamDeque {
struct StreamPtr {
  IStream_s0060_c780* mpObject;
  ~StreamPtr() {
    if (mpObject) mpObject->Release();
  }
  StreamPtr& operator=(const StreamPtr& x) {
    IStream_s0060_c780* const pObject = x.mpObject;
    IStream_s0060_c780* const pTemp = mpObject;
    if (pObject != pTemp) {
      if (pObject) pObject->AddRef();
      mpObject = pObject;
      if (pTemp) pTemp->Release();
    }
    return *this;
  }
};
}
namespace StreamDeque {
struct Iterator {
  StreamPtr* mpCurrent;
  StreamPtr* mpBegin;
  StreamPtr* mpEnd;
  StreamPtr** mpCurrentArrayPtr;
  enum { kSubarraySize = 64 };
  Iterator& operator++() {
    ++mpCurrent;
    if (mpCurrent == mpEnd) {
      ++mpCurrentArrayPtr;
      mpBegin = *mpCurrentArrayPtr;
      mpEnd = mpBegin + kSubarraySize;
      mpCurrent = mpBegin;
    }
    return *this;
  }
  Iterator& operator--() {
    if (mpCurrent == mpBegin) {
      --mpCurrentArrayPtr;
      mpBegin = *mpCurrentArrayPtr;
      mpEnd = mpBegin + kSubarraySize;
      mpCurrent = mpEnd;
    }
    --mpCurrent;
    return *this;
  }
  void SetSubarray(StreamPtr** pArrayPtr) {
    mpCurrentArrayPtr = pArrayPtr;
    mpBegin = *pArrayPtr;
    mpEnd = mpBegin + kSubarraySize;
  }
};
}
namespace StreamDeque {
enum Side { kSideFront, kSideBack };
}
namespace StreamDeque {
template <typename T>
inline const T& max_alt(const T& a, const T& b) { return a < b ? b : a; }
}
namespace StreamDeque {
#define USED_PTR_SPACE ((unsigned int)((char*)mItEnd.mpCurrentArrayPtr - (char*)mItBegin.mpCurrentArrayPtr) + sizeof(void*))
}
namespace StreamDeque {
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
}
namespace StreamDeque {
extern "C" __declspec(dllimport) void* __cdecl memmove(void*, const void*, unsigned int);
}
namespace StreamDeque {
struct DequeBase {
  StreamPtr** mpPtrArray;    // +0x0
  unsigned int mnPtrArraySize;  // +0x4
  Iterator mItBegin;         // +0x8
  Iterator mItEnd;           // +0x18

  void DoFreeSubarray(StreamPtr* p) {
    if (p) EASTL_allocator_deallocate(p);
  }
  __forceinline void DoDestroyRange(StreamPtr* pBegin, StreamPtr* const& pEnd) {
    for (; pBegin < pEnd; ++pBegin) pBegin->~StreamPtr();
  }
  void clear();
  void DoReallocPtrArray(unsigned int nAdditionalCapacity, Side allocationSide);
};
}
namespace SP {
class AtomicRefCounted {
 public:
  virtual ~AtomicRefCounted() {}
  volatile long mRefCount;  // +0x4
  int AddRef() { return _InterlockedExchangeAdd(&mRefCount, 1) + 1; }
  int Release() {
    const int n = _InterlockedExchangeAdd(&mRefCount, -1) - 1;
    if (n == 0) {
      _InterlockedExchange(&mRefCount, 1);
      delete this;
      return 0;
    }
    return n;
  }
};
}
namespace SP {
struct AtomicRef {
  AtomicRefCounted* mpObject;
  ~AtomicRef();   // 0x0060d210
  AtomicRef& reset();  // 0x0060d240
};
}
namespace SP {
struct HashNode {
  uint32_t mValue[2];
  HashNode* mpNext;  // +0x8
};
}
namespace SP {
struct HashIterator {
  HashNode* mpNode;
  HashNode** mpBucket;
  HashIterator(const HashIterator& x) : mpNode(x.mpNode), mpBucket(x.mpBucket) {}
  HashIterator& operator++() {
    mpNode = mpNode->mpNext;
    while (mpNode == 0) mpNode = *++mpBucket;
    return *this;
  }
};
}
namespace Pollinator {
class __declspec(novtable) IMessageBase {
 public:
  virtual void m0() = 0;
};
}
namespace Pollinator {
class DefaultRefCounted {
 public:
  DefaultRefCounted() : mnRefCount(0) {}
  ~DefaultRefCounted() {}
  virtual void d0();
  virtual void d1();
  virtual void d2();
  virtual void d3();
  int mnRefCount;  // +0x8
};
}
namespace Pollinator {
class cJobResultMessage : public IMessageBase, public DefaultRefCounted {
 public:
  cJobResultMessage(uint32_t nJobID, uint32_t nResult, SP::AtomicRefCounted* pData);
  virtual void m0();
  virtual void d0();
  uint32_t mnJobID;                   // +0xc
  uint32_t mnResult;                  // +0x10
  SP::AtomicRefCounted* mpData;       // +0x14
};
}
class IMessagingServer {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5)
  virtual void Post(const void* pMessageType, void* pMessage, int, int);  // +0x18
};
IMessagingServer* GetMessagingServer();  // 0x00883860
extern const char kJobResultMessageType[];  // 0x0164d214
namespace SP {
struct cCommandBase {
  ~cCommandBase();  // 0x0083c750
  char pad[0x10];
};
}
namespace SP {
extern void* gPaintSystemVtbl[];  // 0x013eb394
}
namespace SP {
class cPollinatorCheat_s0060_c780 : public cCommandBase {
 public:
  cPollinatorCheat_s0060_c780* DeletingDtor(unsigned char flags);
  void* mpVtbl10;  // +0x10
};
}
// ---- items of slice s0060c780 end

// ---- items of slice s0060ea40 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange)
#define EASTL_ALLOCATOR_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"
namespace eastl {
struct allocator_s0060_ea40 {
    void* allocate(size_t n) { return EASTL_allocator_allocate((uint32_t)n, "Editor", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1); }
    void deallocate(void* p) { EASTL_allocator_deallocate(p); }
};  // namespace eastl
}
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
struct IObj4 {
    virtual void v0();
    virtual void AddRef4();   // +0x4
    virtual void Release8();  // +0x8
};
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
struct UploadQueue {
    QValue* mpBegin;     // +0x0
    QValue* mpEnd;       // +0x4
    QValue* mpCapacity;  // +0x8
    uint32_t mPad0c;     // +0xc

    void DoInsertValue(QValue* position, const QValue* value);  // 0x0060ec20
    void push_back(const QValue& value);                        // 0x0060f080
};
struct EmptyQueue {
    char* mpBegin;  // +0x0
    char* mpEnd;    // +0x4
    char* mpCap;    // +0x8
};
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
struct DequeIterator_s0060_ea40 {
    T* mpCurrent;
    T* mpBegin;
    T* mpEnd;
    T** mpCurrentArrayPtr;
    DequeIterator_s0060_ea40() {}
    DequeIterator_s0060_ea40(const DequeIterator_s0060_ea40& x) : mpCurrent(x.mpCurrent), mpBegin(x.mpBegin), mpEnd(x.mpEnd), mpCurrentArrayPtr(x.mpCurrentArrayPtr) {}
    void SetSubarray(T** p) {
        mpCurrentArrayPtr = p;
        mpBegin = *p;
        mpEnd = mpBegin + kSubarraySize;
    }
    DequeIterator_s0060_ea40& operator++() {
        if (++mpCurrent == mpEnd) {
            SetSubarray(mpCurrentArrayPtr + 1);
            mpCurrent = mpBegin;
        }
        return *this;
    }
    DequeIterator_s0060_ea40& operator+=(int n);  // 0x007a9a80
};
template <class T>
inline bool operator==(const DequeIterator_s0060_ea40<T>& a, const DequeIterator_s0060_ea40<T>& b) { return a.mpCurrent == b.mpCurrent; }
template <class T>
inline bool operator!=(const DequeIterator_s0060_ea40<T>& a, const DequeIterator_s0060_ea40<T>& b) { return a.mpCurrent != b.mpCurrent; }
template <class T, int kSubarraySize = 64>
struct deque {
    typedef DequeIterator_s0060_ea40<T, kSubarraySize> iterator;
    T** mpPtrArray;
    uint32_t mnPtrArraySize;
    iterator mItBegin;
    iterator mItEnd;
    eastl::allocator_s0060_ea40 mAllocator;
    enum Side { kSideFront, kSideBack };
    void DoReallocPtrArray(uint32_t nAdditionalCapacity, Side allocationSide);
    T* DoAllocateSubarray() { return (T*)mAllocator.allocate(kSubarraySize * sizeof(T)); }
    void DoFreeSubarray(T* p) { if (p) mAllocator.deallocate(p); }
    void erase(iterator first, iterator last);
    void PushSlow(const T& value, bool bFront);
    iterator insert(iterator position, const T& value);
};
template class deque<TransactionPtr>;
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
void RBTreeErase();      // 0x00921880
// ---- items of slice s0060ea40 end

// ---- items of slice s0060f910 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
struct allocator_s0060_f910 {
    void* allocate(size_t n) { return EASTL_allocator_allocate((uint32_t)n, "Editor", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1); }
    void deallocate(void* p) { EASTL_allocator_deallocate(p); }
};  // namespace eastl
}
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
struct DequeIterator_s0060_f910 {
    T* mpCurrent;
    T* mpBegin;
    T* mpEnd;
    T** mpCurrentArrayPtr;
    DequeIterator_s0060_f910() {}
    DequeIterator_s0060_f910(const DequeIterator_s0060_f910& x) : mpCurrent(x.mpCurrent), mpBegin(x.mpBegin), mpEnd(x.mpEnd), mpCurrentArrayPtr(x.mpCurrentArrayPtr) {}
    void SetSubarray(T** p) { mpCurrentArrayPtr = p; mpBegin = *p; mpEnd = mpBegin + kSubarraySize; }
    DequeIterator_s0060_f910& operator--() {
        if (mpCurrent == mpBegin) {
            --mpCurrentArrayPtr;
            SetSubarray(mpCurrentArrayPtr);
            mpCurrent = mpEnd;
        }
        --mpCurrent;
        return *this;
    }
    DequeIterator_s0060_f910& operator++() {
        if (++mpCurrent == mpEnd) {
            SetSubarray(mpCurrentArrayPtr + 1);
            mpCurrent = mpBegin;
        }
        return *this;
    }
};
void PushFrontSlowHelper(void* value);  // 0x0060db40
template <class T, int kSubarraySize = 64>
struct deque_s0060_f910 {
    typedef DequeIterator_s0060_f910<T, kSubarraySize> iterator;
    T** mpPtrArray;
    uint32_t mnPtrArraySize;
    iterator mItBegin;
    iterator mItEnd;
    eastl::allocator_s0060_f910 mAllocator;
    void push_front(const T& value) {
        if (mItBegin.mpCurrent == mItBegin.mpBegin) {
            PushFrontSlowHelper((void*)&value);
        } else {
            --mItBegin.mpCurrent;
            *mItBegin.mpCurrent = value;
        }
    }
};
typedef deque_s0060_f910<AutoRefCount<cITransaction>, 64> TransactionDeque;
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
namespace SP {
struct cPollinator_s0060_f910 {
    virtual void v0();
    virtual void v1();
    uint32_t mField4;                    // +0x4
    TransactionDeque mTransactionQueue;  // +0x8
    char pad34[0xf1 - 0x34];
    char mEnabled;                       // +0xf1

    void ProcessTransactionQueue();                       // 0x00610140
    void CreateMyFeed(void* a, void* b, int c);           // 0x006104f0
    void UpdateMyFeed(void* a, void* b, int c);           // 0x006105d0
    void DeleteMyFeed(void* a);                           // 0x006106f0
    void SubscribeToFeed(void* a);                        // 0x00610780
    void UnsubscribeToFeed(void* a);                      // 0x00610810
    void PostGetAssetFeed(void* a, void* b);              // 0x006103d0
    void PostEatFeed(void* a);                            // 0x00610460
};  // namespace SP
}
// ---- items of slice s0060f910 end

// ---- items of slice s006108a0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace eastl {
 struct allocator_s0061_08a0 {
    void* allocate(size_t n) { return EASTL_allocator_allocate((uint32_t)n, "Editor", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1); }
    void deallocate(void* p) { EASTL_allocator_deallocate(p); }
}; 
}
template <class T, int N = 64>
struct DequeIterator_s0061_08a0 {
    T* mpCurrent; T* mpBegin; T* mpEnd; T** mpCurrentArrayPtr;
    DequeIterator_s0061_08a0() {}
    DequeIterator_s0061_08a0(const DequeIterator_s0061_08a0& x) : mpCurrent(x.mpCurrent), mpBegin(x.mpBegin), mpEnd(x.mpEnd), mpCurrentArrayPtr(x.mpCurrentArrayPtr) {}
    void SetSubarray(T** p) { mpCurrentArrayPtr = p; mpBegin = *p; mpEnd = mpBegin + N; }
    DequeIterator_s0061_08a0& operator--() {
        if (mpCurrent == mpBegin) { --mpCurrentArrayPtr; SetSubarray(mpCurrentArrayPtr); mpCurrent = mpEnd; }
        --mpCurrent; return *this;
    }
    DequeIterator_s0061_08a0& operator++() {
        if (++mpCurrent == mpEnd) { SetSubarray(mpCurrentArrayPtr + 1); mpCurrent = mpBegin; }
        return *this;
    }
};
template <class T, int N = 64>
struct deque_s0061_08a0 {
    typedef DequeIterator_s0061_08a0<T, N> iterator;
    T** mpPtrArray; uint32_t mnPtrArraySize; iterator mItBegin; iterator mItEnd; eastl::allocator_s0061_08a0 mAllocator;
    void push_front(const T& value) {
        if (mItBegin.mpCurrent == mItBegin.mpBegin) {
            PushFrontSlowHelper((void*)&value);
        } else {
            --mItBegin.mpCurrent;
            *mItBegin.mpCurrent = value;
        }
    }
};
typedef deque_s0061_08a0<AutoRefCount<cITransaction>, 64> TransactionDeque_s0061_08a0;
struct RbNodeBase { RbNodeBase* mpRight; RbNodeBase* mpLeft; RbNodeBase* mpParent; char mColor; };
RbNodeBase* RBTreeIncrementNode(RbNodeBase* node);  // 0x00921580
namespace SP {
struct cPollinator_s0061_08a0 {
    virtual void v0();
    virtual void v1();
    uint32_t mField4;                                 // +0x4
    TransactionDeque_s0061_08a0 mTransactionQueue;               // +0x8
    RbNodeBase mActiveAnchor;                         // +0x34 (approx)
    char pad44[0xf1 - 0x44];
    char mEnabled;                                    // +0xf1

    void CancelTransactions(int id);                  // 0x00611170
    void CancelAllTransactions();                     // 0x00611540
    void PostGetAssetFeedEx(void* a, void* b);        // 0x00610c20
    void ProcessTransactionQueue();                   // 0x00610140 (decl here for reuse)
};
}
// ---- items of slice s006108a0 end

// ---- items of slice s00612270 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned __int64 u64;
void __cdecl operator delete[](void* p);  // 0x00f47380
struct ResourceKey_s0061_2270 { uint32_t a, b, c; };
struct ITx {
    virtual int v0();
    virtual int AddRef();
    virtual int Release();
};
struct AutoTx {
    ITx* mpObject;
    AutoTx(ITx* p) : mpObject(p) {
        if (mpObject) mpObject->AddRef();
    }
    AutoTx(const AutoTx& x) : mpObject(x.mpObject) {
        if (mpObject) mpObject->AddRef();
    }
    ~AutoTx() {
        if (mpObject) mpObject->Release();
    }
};
struct TxQueue {
    char pad0[0x18];
    AutoTx* mpCurrent;  // +0x18
    char pad1c[4];
    AutoTx* mpEnd;      // +0x20
    char pad24[0x2c];
    void PushBackSlow(const AutoTx* pItem);   // 0x0060dbd0
    bool Push(ITx* pTx, bool bFront);         // 0x0060eaf0 (ret 8)
    void push_back(const AutoTx& v) {
        AutoTx* const pSlot = mpCurrent;
        if (pSlot + 1 == mpEnd) {
            PushBackSlow(&v);
        } else {
            mpCurrent = pSlot + 1;
            ::new (pSlot) AutoTx(v);
        }
    }
};
namespace SP {
namespace Pollen {
struct cAssetDirectory_s0061_2270 {
    void Flush();  // 0x0054efb0
    u64 GetLastRefreshTime(uint32_t key);                         // 0x0054e9a0 (ret 4, edx:eax)
    bool GetServerId(const ResourceKey_s0061_2270* pKey, u64* pId, bool b);  // 0x0054e530 (ret 0xc)
};  // namespace Pollen
}
}
namespace SP {
namespace FunctionalMatch {
struct Constraint_s0061_2270;
}
}
namespace SP {
namespace FunctionalMatch {
struct CVec {
    Constraint_s0061_2270* mpBegin;
    Constraint_s0061_2270* mpEnd;
    Constraint_s0061_2270* mpCapacity;
    const char* mpName;
    uint32_t mFlags;
    CVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    CVec(const CVec& x);                                          // 0x004e38d0
    void DoDestroyValues(Constraint_s0061_2270* first, Constraint_s0061_2270* last);    // 0x004e39a0
    void DoInsertValue(Constraint_s0061_2270* pos, const Constraint_s0061_2270& v);     // 0x004e39d0
    ~CVec() {
        DoDestroyValues(mpBegin, mpEnd);
        if (mpBegin && ((int*)mpBegin)[-1]) operator delete[](mpBegin);
    }
    inline void push_back(const Constraint_s0061_2270& v);
};
}
}
namespace SP {
namespace FunctionalMatch {
struct Constraint_s0061_2270 {
    uint32_t mParameter;
    uint32_t mType;
    union {
        struct { int mMin; int mMax; } mIntVal;
        struct { float mMin; float mMax; } mFloatVal;
    };
    CVec mConstraints;
    Constraint_s0061_2270(int sentinel);                              // 0x00558830
    Constraint_s0061_2270(uint32_t param, int op, int value);          // 0x00558960
    Constraint_s0061_2270(int any, CVec constraints);                  // 0x00558ae0
};
}
}
namespace SP {
namespace FunctionalMatch {
inline void CVec::push_back(const Constraint_s0061_2270& v) {
    if (mpEnd < mpCapacity) {
        ::new (mpEnd++) Constraint_s0061_2270(v);
    } else {
        DoInsertValue(mpEnd, v);
    }
}
}
}
namespace SP {
struct U32Range { uint32_t* mpBegin; uint32_t* mpEnd; };
}
namespace SP {
struct cFilterOwner {
    char pad[0x1c];
    U32Range mList;
    U32Range* GetList();  // 0x006b42e0 (lea eax,[ecx+0x1c])
};
}
namespace SP {
struct cPollinator_s0061_2270 {
    virtual void v0();
    virtual bool HandleMessage(uint32_t id, void* msg);  // 0x00611860 (SP::cPollinator::HandleMessage)
    char pad4[4];
    TxQueue mQueue;                                // +8
    Pollen::cAssetDirectory_s0061_2270* mpAsssetDirectory;    // +0x58
    cFilterOwner* mpFilters;                       // +0x5c
    char pad60[0x54];
    char* mpRecordsA;                              // +0xb4
    char* mpRecordsAEnd;                           // +0xb8
    char padbc[0x0c];
    char* mpRecordsB;                              // +0xc8
    char* mpRecordsBEnd;                           // +0xcc
    char padd0[0x0c];
    char* mpRecordsC;                              // +0xdc
    char* mpRecordsCEnd;                           // +0xe0
    char pade4[0x0d];
    bool mbEnabled;                                // +0xf1
    char padf2[0x1a];
    int mRefreshInterval;                          // +0x10c
    void FUN_006103d0(uint32_t lo, uint32_t hi);   // 0x006103d0
    void ProcessTransactionQueue();                // 0x00610140
    void ProcessTransactionTick();                 // 0x00612270
};
}
namespace SP {
cPollinator_s0061_2270* GetPollinator();  // 0x0067cb30
}
struct cMessageServer {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9(); virtual void s10();
    virtual void SetHandlerPriority(void* pHandler, uint32_t id, int priority);  // +0x2c
};
cMessageServer* GetMessageServer();  // 0x0067dcc0
struct FloodHandler {
    void* mVtbl;
    int mnFlood;  // cheat + 0x14
    bool HandleMessage(uint32_t id, void* pMessage);
};
// ---- items of slice s00612270 end

// @ 0x0060ccc0
namespace SP {
UploadEntry::UploadEntry(const ResourceKey& key, bool bFlag0, bool bFlag1)
: mKey(key), mbFlag0(bFlag0), mbFlag1(bFlag1) {}
}  // namespace SP






// @ 0x0060ccf0
namespace SP {
bool GetTypeFromName(const char* pName, uint32_t* pType)
{
  const uint32_t nHash = FNV1(pName, 0x811c9dc5, 1);
  switch (nHash) {
    case 0x72c49181:
    case 0x4178b8e8:
    case 0x2a5147a9:
    case 0x1a4e0708:
    case 0x1f2a25b6:
    case 0x2090a11b:
    case 0x37148141:
    case 0x372e2c04:
    case 0x47c10953:
    case 0x441cd3e6:
    case 0x449c040f:
    case 0x4e3f7777:
    case 0x65672ade:
    case 0xbc1041e6:
    case 0x9ad7d4aa:
    case 0x98e03c0d:
    case 0x7d433fad:
    case 0x8f963dcb:
    case 0x99e92f05:
    case 0x9ea3031a:
    case 0xb8669ec9:
    case 0xc15695da:
    case 0xbcd73e89:
    case 0xbdd15f3d:
    case 0xc0b74287:
    case 0xccc35c46:
    case 0xdfad9f51:
    case 0xf670aa43:
      *pType = nHash;
      return true;
  }
  return false;
}
}  // namespace SP






// @ 0x0060ce10
namespace SP {
int ClassifyCommand(short nCommand, cAchievementSource* pSource)
{
  switch (nCommand) {
    case 0:
      return 0;
    case 2:
    case 4:
    case 5:
    case 6:
    case 7:
    case 0xd:
      return 1;
    case 9:
      if (pSource) {
        const int nID = pSource->mnID;
        if (nID == 0x1a2) return 5;
        if (nID == 0x1c3) return 7;
        if (nID == 0x1c4) return 8;
      }
      return 2;
    case 10:
      return 4;
    case 8:
      return 6;
    case 1:
    case 3:
    case 0xb:
    case 0xc:
    case 0xe:
      return 3;
  }
  return 3;
}
}  // namespace SP






// @ 0x0060cec0
namespace SP {
void cPollinator_s0060_c780::SetEnabledState(int nState)
{
  const bool bWasEnabled = mbPollinationEnabled;
  switch (nState) {
    case 0x4c4d2c3:
      mbPollinationEnabled = true;
      mbShutdownInProgress = false;
      break;
    case 0x4c4d2cd:
      mbPollinationEnabled = false;
      mbShutdownInProgress = false;
      break;
    case 0x4c4d2df:
      mbPollinationEnabled = true;
      mbShutdownInProgress = true;
      break;
    default:
      mbPollinationEnabled = false;
      mbShutdownInProgress = false;
      break;
  }
  if (!bWasEnabled && mbPollinationEnabled) MessageServer()->MessageSend(0x3743e04, 0, 0);
}
}  // namespace SP






// @ 0x0060cf30
namespace SP {
void __stdcall OnGameEvent(cGameEventMessage* pMessage)
{
  cAchievementsController* const pController = GetAchievementsController();
  if (pController) {
    switch (pMessage->mnEventID) {
      case 0x2b978c46:
      case 0x3d97a8e4:
        pController->AutoTest(0x2e3fc8f2, 1);
        break;
      case 0x2399be55:
        pController->AutoTest(0x71c5a637, 1);
        break;
      case 0x24682294:
      case 0x476a98c7:
        pController->AutoTest(0xadda228a, 1);
        break;
    }
  }
}
}  // namespace SP






// @ 0x0060cfa0
VariantHelper& VariantHelper::operator=(const uint64_t& value)
{
  if (mFlags & 4) Destruct(1);
  if ((mFlags & 2) && mTypeId != 0xc) {
    Assign(0xc, 0, &value, 8, 1);
    return *this;
  }
  mUint64 = value;
  mTypeId = 0xc;
  mFlags = mFlags & 2;
  return *this;
}






// @ 0x0060d000
ListenerIterator FindAndNotify(ListenerIterator first, ListenerIterator last, ListenerQuery query)
{
  for (; first.mpCurrent != last.mpCurrent; ++first) {
    IListener* const pListener = *first.mpCurrent;
    if (pListener->GetID() == query.mnID) {
      pListener->Notify(8, 0, query.mpData);
      break;
    }
  }
  return first;
}






// @ 0x0060d0a0
ListenerIterator FindReadyAndNotify(ListenerIterator first, ListenerIterator last, void* pData)
{
  for (; first.mpCurrent != last.mpCurrent; ++first) {
    IListener* const pListener = *first.mpCurrent;
    if (pListener->IsReady()) {
      pListener->Notify(8, 0, pData);
      break;
    }
  }
  return first;
}






// @ 0x0060d140
namespace SP {
UploadEntry* uninitialized_copy_entries(const UploadEntry* first, const UploadEntry* last, UploadEntry* dest)
{
  for (; first != last; ++first, ++dest) ::new (dest) UploadEntry(*first);
  return dest;
}
}  // namespace SP






// @ 0x0060d1b0
namespace SP {
cPollinatorCheat_s0060_c780* cPollinatorCheat_s0060_c780::DeletingDtor(unsigned char flags)
{
  mpVtbl10 = gPaintSystemVtbl;
  cCommandBase::~cCommandBase();
  if (flags & 1) EASTL_allocator_deallocate(this);
  return this;
}
}  // namespace SP






// @ 0x0060d1e0
namespace SP {
void __stdcall SendNotificationMessage(void*)
{ MessageServer()->MessageSend(0x6299932, 0, 0); }
}  // namespace SP






// @ 0x0060d210
namespace SP {
AtomicRef::~AtomicRef()
{
  if (mpObject) mpObject->Release();
}
}  // namespace SP






// @ 0x0060d240
namespace SP {
AtomicRef& AtomicRef::reset()
{
  AtomicRefCounted* const p = mpObject;
  if (p) {
    mpObject = 0;
    p->Release();
  }
  return *this;
}
}  // namespace SP






// @ 0x0060d2e0
namespace StreamDeque {
void DequeBase::clear()
{
  if (mItBegin.mpCurrentArrayPtr != mItEnd.mpCurrentArrayPtr) {
    DoDestroyRange(mItBegin.mpCurrent, mItBegin.mpEnd);
    DoDestroyRange(mItEnd.mpBegin, mItEnd.mpCurrent);
    DoFreeSubarray(mItEnd.mpBegin);
  } else {
    DoDestroyRange(mItBegin.mpCurrent, mItEnd.mpCurrent);
  }
  for (StreamPtr** pArray = mItBegin.mpCurrentArrayPtr + 1; pArray < mItEnd.mpCurrentArrayPtr; ++pArray) {
    DoDestroyRange(*pArray, *pArray + Iterator::kSubarraySize);
    DoFreeSubarray(*pArray);
  }
  mItEnd = mItBegin;
}
}  // namespace StreamDeque






// @ 0x0060d3c0
namespace StreamDeque {
void DequeBase::DoReallocPtrArray(unsigned int nAdditionalCapacity, Side allocationSide)
{
  const unsigned int nUsedPtrCount = (unsigned int)(mItEnd.mpCurrentArrayPtr - mItBegin.mpCurrentArrayPtr) + 1;
  const unsigned int nRequiredPtrSpace = nUsedPtrCount + nAdditionalCapacity;
  StreamPtr** pPtrArrayBegin;
  if (mnPtrArraySize <= nRequiredPtrSpace * 2) {
    const unsigned int nNewPtrArraySize = mnPtrArraySize + max_alt(mnPtrArraySize, nAdditionalCapacity) + 2;
    StreamPtr** const pNewPtrArray =
        (StreamPtr**)EASTL_allocator_allocate(nNewPtrArraySize * sizeof(void*), "Editor", 0, 0, "EASTL/allocator.h", 0xd1);
    pPtrArrayBegin = pNewPtrArray + (mItBegin.mpCurrentArrayPtr - mpPtrArray) +
                     ((allocationSide == kSideFront) ? nAdditionalCapacity : 0);
    if (mpPtrArray) memcpy(pPtrArrayBegin, mItBegin.mpCurrentArrayPtr, USED_PTR_SPACE);
    if (mpPtrArray) EASTL_allocator_deallocate(mpPtrArray);
    mpPtrArray = pNewPtrArray;
    mnPtrArraySize = nNewPtrArraySize;
  } else {
    pPtrArrayBegin = mpPtrArray + (((mnPtrArraySize - nRequiredPtrSpace) >> 1) +
                                   ((allocationSide == kSideFront) ? nAdditionalCapacity : 0));
    if (pPtrArrayBegin < mItBegin.mpCurrentArrayPtr)
      memcpy(pPtrArrayBegin, mItBegin.mpCurrentArrayPtr, USED_PTR_SPACE);
    else
      memmove(pPtrArrayBegin + (nUsedPtrCount - ((int)USED_PTR_SPACE >> 2)), mItBegin.mpCurrentArrayPtr, USED_PTR_SPACE);
  }
  mItBegin.SetSubarray(pPtrArrayBegin);
  mItEnd.SetSubarray((pPtrArrayBegin + nUsedPtrCount) - 1);
}
}  // namespace StreamDeque






// @ 0x0060d5d0
namespace SP {
int distance(HashIterator first, HashIterator last)
{
  int n = 0;
  while (first.mpNode != last.mpNode) {
    ++first;
    ++n;
  }
  return n;
}
}  // namespace SP






// @ 0x0060d610
namespace StreamDeque {
Iterator copy(Iterator first, Iterator last, Iterator result)
{
  while (first.mpCurrent != last.mpCurrent) {
    *result.mpCurrent = *first.mpCurrent;
    ++result;
    ++first;
  }
  return result;
}
}  // namespace StreamDeque






// @ 0x0060d6e0
namespace StreamDeque {
Iterator copy_backward(Iterator first, Iterator last, Iterator resultEnd)
{
  while (last.mpCurrent != first.mpCurrent) {
    --last;
    --resultEnd;
    *resultEnd.mpCurrent = *last.mpCurrent;
  }
  return resultEnd;
}
}  // namespace StreamDeque






// @ 0x0060d7a0
namespace Pollinator {
cJobResultMessage::cJobResultMessage(uint32_t nJobID, uint32_t nResult, SP::AtomicRefCounted* pData)
: mnJobID(nJobID), mnResult(nResult), mpData(pData) {
  if (pData) pData->AddRef();
}
}  // namespace Pollinator






// @ 0x0060d800
void NotificationFunction(void*, void*, uint32_t nMessage, uint32_t* pData)
{
  if (nMessage == 0x700af301) {
    IMessagingServer* const pServer = GetMessagingServer();
    void* const pMem = operator new(0x18, "Pollinator/cJobResultMessage", 0, 0, 0, 0);
    Pollinator::cJobResultMessage* const pMessage =
        pMem ? new (pMem) Pollinator::cJobResultMessage(pData[0], pData[1], (SP::AtomicRefCounted*)pData[9]) : 0;
    pServer->Post(kJobResultMessageType, pMessage, 0, 0);
  }
}





// @ 0x0060ea40
QValue* MakeNode(const QValue* src)
{
    char* const pNode = (char*)EASTL_allocator_allocate(0x20, "Editor", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1);
    QValue* const pValue = (QValue*)(pNode + 0x10);
    if (pValue) *pValue = *src;
    return (QValue*)pNode;
}




// @ 0x0060eab0
EmptyQueue* GetEmptyQueueSingleton()
{
    static EmptyQueue s = {0, 0, 0};
    return &s;
}




// @ 0x0060eaf0
template <class T, int kSubarraySize> void deque<T, kSubarraySize>::PushSlow(const T& value, bool bFront)
{
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




// @ 0x0060ee90
void HandlePollinateRequest(cPollinatorReal* self, QValue* entry)
{
    QValue local = *entry;
    local.mKey0 = 0x30bdee3;
    RefCounted* pMeta = 0;
    // resource-manager lookup of the 0x30bdee3 resource would go here
    (void)pMeta;
    (void)self;
}




// @ 0x0060f010
void NextIDReady(cPollinatorReal* self)
{
    UploadQueue& q = self->mUploadQueue;
    if (q.mpBegin == q.mpEnd) return;
    if ((self->mnNextAssetIDLo & self->mnNextAssetIDHi) == 0xffffffff) return;
    QValue local = *q.mpBegin;
    for (QValue* p = q.mpBegin; p + 1 != q.mpEnd; ++p) p[0] = p[1];
    q.mpEnd = q.mpEnd - 1;
    HandlePollinateRequest(self, &local);
}




// @ 0x0060f080
void UploadQueue::push_back(const QValue& value)
{
    QValue* const p = mpEnd;
    if (p < mpCapacity) {
        mpEnd = p + 1;
        ::new (p) QValue(value);
    } else {
        DoInsertValue(p, &value);
    }
}




// @ 0x0060f370
void UpdateAssetVariant(void* self, void* propMgr, uint32_t key)
{
    (void)self;
    (void)propMgr;
    (void)key;
}




// @ 0x0060f4a0
template <class T, int kSubarraySize> void deque<T, kSubarraySize>::erase(iterator first, iterator last)
{
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




// @ 0x0060f700
template <class T, int kSubarraySize> typename deque<T, kSubarraySize>::iterator deque<T, kSubarraySize>::insert(iterator position, const T& value)
{
    if (position == mItEnd) {
        PushSlow(value, false);
        return mItEnd;
    }
    return position;
}




// @ 0x0060f820
RbNode* RbTreeEraseNode(RbTree* self, RbNode* node)
{
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




// @ 0x0060f8a0
void RbTreeNukeSubtree(RbTree* self, RbNode* node)
{
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



// @ 0x0060f910
void cPollinatorInit(void* self)
{ (void)self; }



// @ 0x00610070
void FeedHelper00610070(void* self, void* a)
{ (void)self; (void)a; }



// @ 0x00610140
void SP::cPollinator::ProcessTransactionQueue()
{}



// @ 0x00610460
namespace SP {
void cPollinator_s0060_f910::PostEatFeed(void* a)
{
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
}  // namespace SP



// @ 0x006104f0
namespace SP {
void cPollinator_s0060_f910::CreateMyFeed(void* a, void* b, int c)
{
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
}  // namespace SP



// @ 0x006105d0
namespace SP {
void cPollinator_s0060_f910::UpdateMyFeed(void* a, void* b, int c)
{
    if (mEnabled == 0) return;
    cITransaction* t = 0;
    void* const mem = Alloc0x70(0x70);
    if (mem) t = ((TxnMem*)mem)->EditFeed(1);
    if (t) {
        AutoRefCount<cITransaction> ref(t);
        mTransactionQueue.push_front(ref);
        t->Release();
    }
    ProcessTransactionQueue();
}
}  // namespace SP



// @ 0x006106f0
namespace SP {
void cPollinator_s0060_f910::DeleteMyFeed(void* a)
{
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
}  // namespace SP



// @ 0x00610780
namespace SP {
void cPollinator_s0060_f910::SubscribeToFeed(void* a)
{
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
}  // namespace SP



// @ 0x00610810
namespace SP {
void cPollinator_s0060_f910::UnsubscribeToFeed(void* a)
{
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


// @ 0x006108a0
void FUN_006108a0(void* self, void* a, void* b)
{ (void)self; (void)a; (void)b; }


// @ 0x00610cb0
void FUN_00610cb0(void* self, void* a, void* b)
{ (void)self; (void)a; (void)b; }


// @ 0x00610d40
void FUN_00610d40(void* self, void* a, void* b)
{ (void)self; (void)a; (void)b; }


// @ 0x00610df0
void FUN_00610df0(void* self, int id)
{ (void)self; (void)id; }


// @ 0x00610e90
void FUN_00610e90(void* self, void* a)
{ (void)self; (void)a; }


// @ 0x00610f30
void FUN_00610f30(void* self, void* a, void* b)
{ (void)self; (void)a; (void)b; }


// @ 0x00611170
namespace SP {
__declspec(noinline) void cPollinator_s0061_08a0::CancelTransactions(int id)
{
    // Walk the active-transaction rbtree and remove entries whose transaction id matches.
    for (RbNodeBase* p = mActiveAnchor.mpLeft; p != &mActiveAnchor; p = RBTreeIncrementNode(p)) {
        (void)p;
        (void)id;
    }
    (void)id;
}
}  // namespace SP


// @ 0x006111c0
void FUN_006111c0(void* self, void* a)
{ (void)self; (void)a; }


// @ 0x00611480
void FUN_00611480(void* self, void* a)
{ (void)self; (void)a; }


// @ 0x00611540
namespace SP {
void cPollinator_s0061_08a0::CancelAllTransactions()
{
    CancelTransactions(0x3c88992);
}
}  // namespace SP


// @ 0x00611550
void* FUN_00611550(void* self, void* p)
{ (void)self; return p; }


// @ 0x00611580
void FUN_00611580(void* self, void* a)
{ (void)self; (void)a; }


// @ 0x006116c0
void FUN_006116c0(void* self)
{ (void)self; }

// @ 0x00612980
bool FloodHandler::HandleMessage(uint32_t id, void* pMessage)
{
    SP::cPollinator_s0061_2270* pPollinator = SP::GetPollinator();
    if (id == 0x269c832) {
        if (mnFlood != 0) {
            pPollinator->mpAsssetDirectory->Flush();
            pPollinator->HandleMessage(0x632d709, 0);
            --mnFlood;
            return true;
        }
        FloodHandler* const pCheat = ((uint32_t)this - 0x10) ? this : 0;
        cMessageServer* const pServer = GetMessageServer();
        pServer->SetHandlerPriority(pCheat, 0x269c832, -10000);
        pPollinator->ProcessTransactionTick();
    }
    return true;
}
