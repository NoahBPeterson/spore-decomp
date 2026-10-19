// src/game/SPEditors/SPPollinator.cpp -- migrated from slice(s) s00611860, s0060d860, s00612270, s006108a0, s0060f910, s0060ea40, s0060c780 by tools/migrate/rewrite.py
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
#include "EA/Messaging/IMessageRC.h"
#include "SP/cPropertyManager.h"
#include "SP/cTextureAsyncQueueEntry.h"
#include "SP/Feed/FeedDescription.h"
#include "SP/Pollen/cAssetDirectory.h"
#include "SP/Pollen/cSnapshotUploadTransaction.h"
#include "SP/Pollen/cTransactionQueue.h"
#include "SP/Pollen/cYouTubeAuthenticationTransaction.h"
#include "SP/Pollen/cYouTubeVideoURLTransaction.h"
#include "SP/Pollen/cYouTubeVideoUploadTransaction.h"

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
struct TxnMem_s0061_08a0 {
    cITransaction* GetAssetFeedEx(void* a, void* b);  // 0x0061a8b0
};
void* __cdecl Alloc0x110(size_t);
namespace SP {
void ProcessTransactionQueueGlobal();
}
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

// ---- items of slice s0060d860 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" long _InterlockedDecrement(volatile long*);
#pragma intrinsic(_InterlockedExchangeAdd, _InterlockedExchange, _InterlockedDecrement)
namespace EA {
namespace ResourceMan {
struct Key_s0060_d860 {
    uint32_t instanceID, typeID, groupID;
};
}
}
namespace EA {
using ResourceMan::Key_s0060_d860;
}
namespace EA {
struct AtomicInt {
    volatile long mValue;
    long Increment() { return _InterlockedExchangeAdd(&mValue, 1) + 1; }
    long Decrement() { return _InterlockedDecrement(&mValue); }
    void SetValue(long v) { _InterlockedExchange(&mValue, v); }
};
}
namespace EA {
struct RefCounted_s0060_d860 {
    virtual ~RefCounted_s0060_d860();
    AtomicInt mRefCount;
    void AddRef() { mRefCount.Increment(); }
    void Release() {
        long c = mRefCount.Decrement();
        if (c == 0) {
            mRefCount.SetValue(1);
            delete this;
        }
    }
};
}
namespace EA {
template <class T>
struct AutoRefCount_s0060_d860 {
    T* mpObject;
    ~AutoRefCount_s0060_d860() {
        if (mpObject) mpObject->Release();
    }
};
}
namespace EA {
struct U64Pair {
    uint32_t lo, hi;
};
}
namespace EA {
struct Variant_s0060_d860 {
    char mData[16];
    uint16_t mFlags;
    uint16_t mTypeId;
    void Construct(const U64Pair* p);                                                     // 0x0060cfa0
    void Construct(uint32_t type, uint32_t size, uint32_t a, uint32_t b, uint32_t c);      // 0x0093dd80
    void Destruct(int);                                                                    // 0x0093db80
    Variant_s0060_d860(const U64Pair* p) {
        mTypeId = 0;
        mFlags = 0;
        Construct(p);
    }
    Variant_s0060_d860(uint32_t a, uint32_t b) {
        mFlags = 0;
        mTypeId = 0;
        Construct(0xc, 0x18, a, 8, b);
    }
    ~Variant_s0060_d860() {
        if (mFlags & 4) Destruct(0);
    }
};
}
using EA::Key_s0060_d860;
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
struct allocator_s0060_d860 {
    void* allocate(size_t n) { return EASTL_allocator_allocate(n, "Editor", 0, 0, EASTL_ALLOCATOR_FILE, 0xd1); }
    void deallocate(void* p) { EASTL_allocator_deallocate(p); }
};
}
namespace eastl {
template <class T, int kSubarraySize = 64>
struct DequeIterator_s0060_d860 {
    T* mpCurrent;
    T* mpBegin;
    T* mpEnd;
    T** mpCurrentArrayPtr;

    DequeIterator_s0060_d860() {}
    DequeIterator_s0060_d860(const DequeIterator_s0060_d860& x)
        : mpCurrent(x.mpCurrent), mpBegin(x.mpBegin), mpEnd(x.mpEnd), mpCurrentArrayPtr(x.mpCurrentArrayPtr) {}
    void SetSubarray(T** pCurrentArrayPtr) {
        mpCurrentArrayPtr = pCurrentArrayPtr;
        mpBegin = *pCurrentArrayPtr;
        mpEnd = mpBegin + kSubarraySize;
    }
    DequeIterator_s0060_d860& operator++() {
        if (++mpCurrent == mpEnd) {
            SetSubarray(mpCurrentArrayPtr + 1);
            mpCurrent = mpBegin;
        }
        return *this;
    }
    DequeIterator_s0060_d860& operator+=(int n);  // 0x007a9a80
    DequeIterator_s0060_d860& operator-=(int n) { return (*this).operator+=(-n); }
    DequeIterator_s0060_d860 operator+(int n) const { return DequeIterator_s0060_d860(*this).operator+=(n); }
    DequeIterator_s0060_d860 operator-(int n) const { return DequeIterator_s0060_d860(*this).operator-=(n); }
};
}
namespace eastl {
template <class T>
inline bool operator==(const DequeIterator_s0060_d860<T>& a, const DequeIterator_s0060_d860<T>& b) { return a.mpCurrent == b.mpCurrent; }
}
namespace eastl {
template <class T>
inline bool operator!=(const DequeIterator_s0060_d860<T>& a, const DequeIterator_s0060_d860<T>& b) { return a.mpCurrent != b.mpCurrent; }
}
namespace eastl {
template <class T, int kSubarraySize = 64>
struct deque_s0060_d860 {
    typedef DequeIterator_s0060_d860<T, kSubarraySize> iterator;
    T** mpPtrArray;
    uint32_t mnPtrArraySize;
    iterator mItBegin;
    iterator mItEnd;
    allocator_s0060_d860 mAllocator;

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
    ~deque_s0060_d860();                              // 0x0060e660
};
}
namespace eastl {
template <class T, int N>
deque_s0060_d860<T, N>::~deque_s0060_d860() {
    for (iterator itCurrent(mItBegin); itCurrent != mItEnd; ++itCurrent) itCurrent.mpCurrent->~T();
    if (mpPtrArray) {
        T** const pEnd = mItEnd.mpCurrentArrayPtr + 1;
        for (T** pCurrent = mItBegin.mpCurrentArrayPtr; pCurrent < pEnd; ++pCurrent) DoFreeSubarray(*pCurrent);
        DoFreePtrArray(mpPtrArray);
    }
}
}
namespace SP {
namespace Pollen {
struct cAssetMetadata_s0060_d860 {
    virtual int AddRef();
    virtual int Release();
    const EA::U64Pair* GetServerId();  // 0x005507a0 (not virtual)
};
}
}
namespace SP {
namespace Pollen {
bool GetAssetMetadata(const Key_s0060_d860& key, cAssetMetadata_s0060_d860** ppMetadata);  // 0x00552450
}
}
namespace SP {
namespace Pollen {
struct cAssetDirectory_s0060_d860 {
    bool GetLocalKey(uint64_t serverId, Key_s0060_d860* pKey) const;                       // 0x0054e460
    bool GetServerId(const Key_s0060_d860& key, uint64_t* pServerId, bool bLoad) const;    // 0x0054e530
};
}
}
namespace SP {
struct cPropertyManager_s0060_d860 {
    void SetProperty(uint32_t id, EA::Variant_s0060_d860* v);                              // 0x0061fdb0
    void SetProperty2(uint32_t id, uint32_t lo, uint32_t hi, EA::Variant_s0060_d860* v);   // 0x0061fee0
};
}
namespace SP {
cPropertyManager_s0060_d860* GetPropertyManager();  // 0x0061df20
}
namespace SP {
struct cPollinator_s0060_d860 {
    virtual void v0();
    virtual bool HandleMessage(uint32_t id, void* msg);  // 0x00611860 (SP::cPollinator::HandleMessage)
    char pad[0x54];
    Pollen::cAssetDirectory_s0060_d860* mpAsssetDirectory;  // +0x58

    void UpdateProperty(uint32_t id, const Key_s0060_d860& key);                                  // 0x0060d860
    void UpdateProperty2(uint32_t id, const Key_s0060_d860* key, EA::Variant_s0060_d860* v);                 // 0x0060d920
    void UpdatePropertyInt(uint32_t id, const Key_s0060_d860* key, uint32_t a, uint32_t b);       // 0x0060e600
};
}
template struct eastl::deque_s0060_d860<QueuedPtr>;
struct JobHolder {
    uint32_t mField0;
    QueuedPtr mpMessage;                               // +4
    EA::AutoRefCount_s0060_d860<EA::RefCounted_s0060_d860> mpResponse;       // +8
    void Destroy();
    ~JobHolder() {}
};
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
struct cMessageServer_s0060_d860 {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
    virtual void PostMessage(uint32_t id, void* pMsg, int a, int b);   // +0x18
virtual void s7();
virtual void s8();
    virtual void RegisterHandler(void* pHandler, uint32_t id);          // +0x24
};
cMessageServer_s0060_d860* GetMessageServer_s0060_d860();  // 0x0067dcc0
// ---- items of slice s0060d860 end

// ---- items of slice s00611860 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) unsigned long __cdecl strtoul(const char* s, char** end, int base);
extern int g_DefaultVariantInt;                                  // 0x015d1160
#define PVCAT2(a, b) a##b
#define PVCAT(a, b) PVCAT2(a, b)
#define PV_s0061_1860 virtual void PVCAT(pv_, __COUNTER__)();
#define PV2 PV_s0061_1860 PV_s0061_1860
#define PV4 PV2 PV2
#define PV8 PV4 PV4
namespace eastl {
struct allocator_s0061_1860 {
    allocator_s0061_1860() {}
    void deallocate(void* p, size_t) { operator delete[](p); }
};
}
namespace eastl {
struct string {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    allocator_s0061_1860 mAllocator;

    struct CtorSprintf {};
    string(const char* p, const allocator_s0061_1860& a = allocator_s0061_1860());   // 0x0057ed80
    string(const string& x);                                     // 0x0057cb10
    string(CtorSprintf, const char* pFormat, ...);               // 0x00472f50
    ~string() { DeallocateSelf(); }                              // 0x00530670 when not inlined
    void DeallocateSelf()
    {
        if ((mpCapacity - mpBegin) > 1)
            DoFree(mpBegin, (size_t)(mpCapacity - mpBegin));
    }
    void DoFree(char* p, size_t n)
    {
        if (p)
            mAllocator.deallocate(p, n);
    }
    const char* c_str() const { return mpBegin; }
    bool empty() const { return mpBegin == mpEnd; }
};
}
namespace eastl {
bool operator==(const string& a, const string& b);              // 0x00554fb0
}
namespace EA {
struct Variant_s0061_1860 {
    void* mValue;                                                // +0x00 (inline storage / pointer)
    uint32_t mStorage[3];
    uint16_t mFlags;                                             // +0x10
    uint16_t mTypeId;                                            // +0x12
    Variant_s0061_1860& operator=(const Variant_s0061_1860& x);                        // 0x00542b80
    void Destruct(int);                                          // 0x0093db80
};
}
namespace EA {
template <typename T> struct VariantT : Variant_s0061_1860 {
    VariantT(const Variant_s0061_1860& x);                                  // 0x0060d990 (int), 0x0060d9c0 (string)
    ~VariantT() { if (mFlags & 4) Destruct(0); }
    T* Get();                                                    // 0x0060d280 (int), 0x0060ebf0 (string)
};
}
namespace EA {
namespace Thread {
struct ThreadTime {
    int mMS;
    ThreadTime(int ms) : mMS(ms) {}
};
}
}
namespace EA {
namespace Thread {
void ThreadSleep(const ThreadTime& t);                           // 0x00921df0
}
}
struct ResourceKey_s0061_1860 {
    uint32_t instanceID, typeID, groupID;
};
struct cIntVariant : EA::Variant_s0061_1860 {
    cIntVariant() { mFlags = 2; mTypeId = 9; }
    cIntVariant& operator=(const EA::Variant_s0061_1860& x) { EA::Variant_s0061_1860::operator=(x); return *this; }
    ~cIntVariant() { if (mFlags & 4) Destruct(0); }
    int* GetPtr()
    {
        if (mTypeId == 9 || mTypeId == 0x10) {
            if (mFlags & 0x30)
                return (int*)mValue;
            return mTypeId ? (int*)this : 0;
        }
        return &g_DefaultVariantInt;
    }
};
struct IResponseCallback {
    PV8 PV2 PV_s0061_1860
    virtual void Complete(int result);                           // +0x2c
};
struct IRequest {
    PV4 PV2 PV_s0061_1860
    virtual EA::Variant_s0061_1860& GetValue(int index);                    // +0x1c
};
struct IRequestMessage {
    PV4
    virtual IRequest* GetRequest();                              // +0x10
    virtual IResponseCallback* GetCallback();                    // +0x14
};
namespace SP {
struct ISporepediaQuery;
}
namespace SP {
namespace Feed {
struct FeedDescription_s0061_1860 {
    uint32_t pad00[0x54 / 4];
    eastl::string mFeedID;                                       // +0x54
    uint32_t pad64[3];
    FeedDescription_s0061_1860& operator=(const FeedDescription_s0061_1860& x);       // 0x005496a0
};                                                               // size 0x70
}
}
namespace SP {
struct FeedDescriptionVector {
    Feed::FeedDescription_s0061_1860* mpBegin;
    Feed::FeedDescription_s0061_1860* mpEnd;
    Feed::FeedDescription_s0061_1860* mpCapacity;
    uint32_t mAllocator[2];
    void push_back(const Feed::FeedDescription_s0061_1860& x);              // 0x00611830
    Feed::FeedDescription_s0061_1860* erase(Feed::FeedDescription_s0061_1860* it);     // 0x00611550
};
}
namespace SP {
struct UIntPair { uint32_t first, second; };
}
namespace SP {
struct UIntVectorMap {
    UIntPair* mpBegin;
    UIntPair* mpEnd;
    uint32_t pad[3];
    UIntPair* find(const uint32_t& key);                         // 0x00ea9bb0
    UIntPair* end() const { return mpEnd; }
};
}
namespace SP {
struct KeySetInsertResult { void* node; bool second; };
}
namespace SP {
struct KeySet {
    KeySetInsertResult insert(const ResourceKey_s0061_1860& key);           // 0x0060ebc0
};
}
namespace SP {
struct cUploadRequest {
    ResourceKey_s0061_1860 mKey;
    bool mbA, mbB;
    cUploadRequest(const ResourceKey_s0061_1860& key, bool a, bool b);      // 0x0060ccc0
};
}
namespace SP {
struct UploadQueue_s0061_1860 {
    void push_back(const cUploadRequest& r);                     // 0x0060f080
};
}
namespace SP {
namespace Pollen {
struct cITransaction_s0061_1860 {};
}
}
namespace SP {
namespace Pollen {
struct cTransactionQueue_s0061_1860 {
    bool Add(cITransaction_s0061_1860* p, bool front);                      // 0x0060eaf0
    void Clear();                                                // 0x00610e90
};
}
}
namespace SP {
namespace Pollen {
struct cAssetDirectory_s0061_1860 {
    void Touch(uint64_t assetID, int flags);                     // 0x0054ed50
};
}
}
namespace SP {
namespace Pollen {
struct cAssetStatusTransaction : cITransaction_s0061_1860 {                                 // 0xf0 bytes
    uint32_t mData[0xf0 / 4];
    static void* operator new(size_t n);                         // 0x006158b0
    cAssetStatusTransaction(int type, uint32_t a, uint32_t b, int c);    // 0x00618d40
    cAssetStatusTransaction(int type, const char* id, int c);            // 0x00618da0
};
}
}
namespace SP {
namespace Pollen {
struct cSnapshotUploadTransaction_s0061_1860 : cITransaction_s0061_1860 {                              // 0x54 bytes
    uint32_t mData[0x54 / 4];
    static void* operator new(size_t n);                         // 0x00615a90
    cSnapshotUploadTransaction_s0061_1860(const ResourceKey_s0061_1860& key, const char* a, const char* b, const char* c, const char* d);  // 0x00619250
};
}
}
namespace SP {
namespace Pollen {
struct cYouTubeAuthenticationTransaction_s0061_1860 : cITransaction_s0061_1860 {                       // 0x3c bytes
    uint32_t mData[0x3c / 4];
    static void* operator new(size_t n);                         // 0x00615af0
    cYouTubeAuthenticationTransaction_s0061_1860(const char* a, const char* b, const char* c, bool d);  // 0x00619300
};
}
}
namespace SP {
namespace Pollen {
struct cYouTubeVideoUploadTransaction_s0061_1860 : cITransaction_s0061_1860 {                          // 0x74 bytes
    uint32_t mData[0x74 / 4];
    static void* operator new(size_t n);                         // 0x00615b20
    cYouTubeVideoUploadTransaction_s0061_1860(const char* a, const char* b, const char* c, const char* d,
                                   const char* e, ResourceKey_s0061_1860 key, uint32_t f);  // 0x00619390
};
}
}
namespace SP {
namespace Pollen {
struct cYouTubeVideoURLTransaction_s0061_1860 : cITransaction_s0061_1860 {                             // 0x48 bytes
    uint32_t mData[0x48 / 4];
    static void* operator new(size_t n);                         // 0x00615b50
    cYouTubeVideoURLTransaction_s0061_1860(const char* a, const char* b, const char* c, const char* d);  // 0x00619470
};
}
}
namespace SP {
namespace Pollen {
struct cTransaction6166e0 : cITransaction_s0061_1860 {                                      // 0x10 bytes
    uint32_t mData[0x10 / 4];
    static void* operator new(size_t n);                         // 0x00615b80
    cTransaction6166e0(uint32_t a, uint32_t b);                  // 0x006166e0
};
}
}
namespace SP {
namespace Pollen {
struct cTransaction616660 : cITransaction_s0061_1860 {                                      // 0x18 bytes
    uint32_t mData[0x18 / 4];
    static void* operator new(size_t n);                         // 0x00615ac0
    cTransaction616660(ISporepediaQuery* q, uint64_t userID);  // 0x00616660
};
}
}
namespace SP {
struct ISporepediaQuery {
    PV4 PV2 PV_s0061_1860
    virtual uint32_t GetCount();                                 // +0x1c
    PV2
    virtual void Reset(int a, int b);                            // +0x28
};
}
namespace SP {
struct cOnlineState {
    uint32_t pad00[0x30 / 4];
    uint64_t mUserID;                                            // +0x30
    ISporepediaQuery* mpQuery;                                   // +0x3c
};
}
namespace SP {
cOnlineState* OnlineState();                                     // 0x0067de90
}
namespace SP {
struct cHTTPClient { void SetTimeout(int a, int ms); };          // 0x00943a30
}
namespace SP {
struct cFeedManager {
    void Init();                                                 // 0x0061faf0
    bool IsBusy();                                               // 0x0061e180
};
}
namespace SP {
cFeedManager* FeedManager();                                     // 0x0061df20
}
namespace SP {
struct IMessageServer_s0061_1860 {
    PV4 PV_s0061_1860
    virtual void PostMSG(uint32_t id, void* a, void* b);         // +0x14
    PV8
    virtual void Update();                                       // +0x38
};
}
namespace SP {
IMessageServer_s0061_1860* MessageServer_s0061_1860();                                 // 0x0067dcc0
}
namespace SP {
struct cAppPropertiesData { uint32_t pad[0x118 / 4]; int mbOffline; };  // +0x118
}
namespace SP {
struct cAppProperties { uint32_t pad[0x3c / 4]; cAppPropertiesData* mpData; };  // +0x3c
}
namespace SP {
extern cAppProperties* sAppProperties;                           // 0x015fd918
}
namespace SP {
struct cPollinator_s0061_1860 {
    void* mpHandlerVtbl;                                         // +0x00 (IHandler)
    cHTTPClient* mpHTTPClient;                                   // +0x04
    Pollen::cTransactionQueue_s0061_1860 mTransactionQueue;                 // +0x08
    uint32_t pad0c[(0x58 - 0x0c) / 4];
    Pollen::cAssetDirectory_s0061_1860* mpAssetDirectory;                   // +0x58
    uint32_t pad5c;
    uint64_t mnNextAssetID;                                      // +0x60
    UploadQueue_s0061_1860 mUploadQueue;                                    // +0x68
    uint32_t pad6c[(0x7c - 0x6c) / 4];
    KeySet mPollinateRequests;                                   // +0x7c
    uint32_t pad80[(0x98 - 0x80) / 4];
    UIntVectorMap mFeedStatus;                                   // +0x98
    uint32_t padac[(0xb0 - 0xac) / 4];
    bool mbShutdownInProgress;                                   // +0xb0
    uint8_t padb1[3];
    FeedDescriptionVector mMySporecasts;                         // +0xb4
    FeedDescriptionVector mMySubscriptions;                      // +0xc8
    uint32_t paddc[(0xf0 - 0xdc) / 4];
    bool mbFlushQueue;                                           // +0xf0
    bool mbPollinationEnabled;                                   // +0xf1
    uint8_t padf2[2];
    UIntVectorMap mAssetStatus;                                  // +0xf4

    void SetEnabledState(uint32_t state);                        // 0x0060cec0
    void HandleTransactionResult(void* pResult);                 // 0x006111c0
    void CancelTransactions(uint32_t id);                        // 0x00611170
    void HandlePollinateRequest(const ResourceKey_s0061_1860& key, bool a, bool b);  // 0x0060ee90
    void ProcessTransactionQueue();                              // 0x00610140
    bool HandleMessage(uint32_t messageID, void* pMessage);  // 0x00611860 (SP::cPollinator::HandleMessage)
};
}
namespace SP {
struct cAssetIDMessage { uint32_t mLow, mHigh; };
}
namespace SP {
struct cSnapshotUploadMessage {
    ResourceKey_s0061_1860 mKey;
    eastl::string mA, mB, mC, mD;                                // +0x0c, +0x1c, +0x2c, +0x3c
};
}
namespace SP {
struct cYouTubeAuthMessage {
    eastl::string mA, mB, mC;                                    // +0x00, +0x10, +0x20
    bool mD;                                                     // +0x30
};
}
namespace SP {
struct cYouTubeUploadMessage {
    eastl::string mA, mB, mC, mD, mE;                            // +0x00 .. +0x40
    ResourceKey_s0061_1860 mKey;                                            // +0x50
    uint32_t mF;                                                 // +0x5c
};
}
namespace SP {
struct cYouTubeURLMessage {
    eastl::string mA, mB, mC, mD;                                // +0x00 .. +0x30
};
}
namespace SP {
struct cPairMessage { uint32_t pad[3]; uint32_t mA, mB; };       // +0x0c, +0x10
}
// ---- items of slice s00611860 end

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

// @ 0x0060d860
namespace SP {
void cPollinator_s0060_d860::UpdateProperty(uint32_t id, const Key_s0060_d860& key)
{
    if (mpAsssetDirectory) {
        EA::U64Pair serverId = {0xffffffff, 0xffffffff};
        Pollen::cAssetMetadata_s0060_d860* pMetadata = 0;
        if (Pollen::GetAssetMetadata(key, &pMetadata)) serverId = *pMetadata->GetServerId();
        if ((serverId.lo & serverId.hi) != 0xffffffff) {
            if (cPropertyManager_s0060_d860* pMgr = GetPropertyManager()) {
                EA::Variant_s0060_d860 v(&serverId);
                pMgr->SetProperty(id, &v);
            }
        }
        if (pMetadata) pMetadata->Release();
    }
}
}  // namespace SP

// @ 0x0060d920
namespace SP {
void cPollinator_s0060_d860::UpdateProperty2(uint32_t id, const Key_s0060_d860* key, EA::Variant_s0060_d860* v)
{
    Pollen::cAssetMetadata_s0060_d860* pMetadata = 0;
    if (Pollen::GetAssetMetadata(*key, &pMetadata)) {
        EA::U64Pair serverId = *pMetadata->GetServerId();
        if ((serverId.lo & serverId.hi) != 0xffffffff) {
            if (cPropertyManager_s0060_d860* pMgr = GetPropertyManager()) pMgr->SetProperty2(id, serverId.lo, serverId.hi, v);
        }
    }
    if (pMetadata) pMetadata->Release();
}
}  // namespace SP

// @ 0x0060dae0
namespace eastl {
template <class T, int N> void deque_s0060_d860<T, N>::pop_back()
{
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
}  // namespace eastl

// @ 0x0060db40
namespace eastl {
template <class T, int N> void deque_s0060_d860<T, N>::DoPushFrontSlow(const T& value)
{
    T valueSaved(value);
    if (mItBegin.mpCurrentArrayPtr == mpPtrArray) DoReallocPtrArray(1, kSideFront);
    mItBegin.mpCurrentArrayPtr[-1] = DoAllocateSubarray();
    mItBegin.SetSubarray(mItBegin.mpCurrentArrayPtr - 1);
    mItBegin.mpCurrent = mItBegin.mpEnd - 1;
    ::new (mItBegin.mpCurrent) T(valueSaved);
}
}  // namespace eastl

// @ 0x0060dbd0
namespace eastl {
template <class T, int N> void deque_s0060_d860<T, N>::DoPushBackSlow(const T& value)
{
    T valueSaved(value);
    if ((mItEnd.mpCurrentArrayPtr - mpPtrArray) + 1 >= (int)mnPtrArraySize) DoReallocPtrArray(1, kSideBack);
    mItEnd.mpCurrentArrayPtr[1] = DoAllocateSubarray();
    ::new (mItEnd.mpCurrent) T(valueSaved);
    mItEnd.SetSubarray(mItEnd.mpCurrentArrayPtr + 1);
    mItEnd.mpCurrent = mItEnd.mpBegin;
}
}  // namespace eastl

// @ 0x0060e540
void PostBehaviorFloat(float value)
{
    BehaviorMessage* pMsg = new ("Pollinator", 0, 0, 0, 0) BehaviorMessage();
    pMsg->mValue = value;
    GetMessageServer_s0060_d860()->PostMessage(0x656435b, pMsg, 0, 0);
}

// @ 0x0060e5b0
void JobHolder::Destroy()
{ this->~JobHolder(); }

// @ 0x0060e600
namespace SP {
void cPollinator_s0060_d860::UpdatePropertyInt(uint32_t id, const Key_s0060_d860* key, uint32_t a, uint32_t b)
{
    EA::Variant_s0060_d860 v(a, b);
    UpdateProperty2(id, key, &v);
}
}  // namespace SP

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

// @ 0x006103d0
namespace SP {
void cPollinator_s0060_f910::PostGetAssetFeed(void* a, void* b)
{
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
}  // namespace SP

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

// @ 0x00610c20
namespace SP {
void cPollinator_s0061_08a0::PostGetAssetFeedEx(void* a, void* b)
{
    if (mEnabled == 0) return;
    cITransaction* t = 0;
    void* const mem = Alloc0x110(0x110);
    if (mem) t = ((TxnMem_s0061_08a0*)mem)->GetAssetFeedEx(a, b);
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
}  // namespace SP

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

// @ 0x00611860
namespace SP {
bool cPollinator_s0061_1860::HandleMessage(uint32_t messageID, void* pMessage)
{
    switch (messageID) {
    case 0x192dc39:
        if (mbPollinationEnabled) {
            uint64_t assetID = *(uint64_t*)pMessage;
            mpAssetDirectory->Touch(assetID, 0);
            mTransactionQueue.Add(new Pollen::cAssetStatusTransaction(3, eastl::string(eastl::string::CtorSprintf(), "%I64u", assetID).c_str(), 0), false);
        }
        break;
    case 0x19168dd:
        if (mbPollinationEnabled) {
            cAssetIDMessage* pID = (cAssetIDMessage*)pMessage;
            mTransactionQueue.Add(new Pollen::cAssetStatusTransaction(0, pID->mLow, pID->mHigh, 0), false);
        }
        break;
    case 0x164d214:
        HandleTransactionResult(pMessage);
        break;
    case 0x238de9c: {
        mbFlushQueue = true;
        mTransactionQueue.Clear();
        mpHTTPClient->SetTimeout(1, 10000);
        cFeedManager* pFeedManager = FeedManager();
        if (pFeedManager) {
            uint32_t i = 0;
            pFeedManager->Init();
            while (pFeedManager->IsBusy() && i++ < 40) {
                ProcessTransactionQueue();
                MessageServer_s0061_1860()->Update();
                EA::Thread::ThreadSleep(EA::Thread::ThreadTime(250));
            }
        }
        break;
    }
    case 0x23a1f6c: {
        IRequestMessage* pRequest = (IRequestMessage*)pMessage;
        IResponseCallback* pCallback = pRequest->GetCallback();
        int value = *EA::VariantT<int>(pRequest->GetRequest()->GetValue(0)).Get();
        if (value) {
            SetEnabledState(0x4c4d2c3);
            pCallback->Complete(0);
        } else {
            mbPollinationEnabled = false;
            mbShutdownInProgress = false;
            pCallback->Complete(0);
        }
        break;
    }
    case 0x23a1f6d: {
        IRequestMessage* pRequest = (IRequestMessage*)pMessage;
        IResponseCallback* pCallback = pRequest->GetCallback();
        eastl::string feedID(*EA::VariantT<eastl::string>(pRequest->GetRequest()->GetValue(0)).Get());
        uint32_t id = strtoul(feedID.c_str(), 0, 0);
        UIntPair* it = mFeedStatus.find(id);
        if (it != mFeedStatus.end() && it->second != 0)
            pCallback->Complete(0);
        else
            pCallback->Complete(2);
        break;
    }
    case 0x30547f1:
        break;
    case 0x3cdd5f9:
        if (pMessage)
            mMySporecasts.push_back(*(Feed::FeedDescription_s0061_1860*)pMessage);
        break;
    case 0x3cf0359: {
        eastl::string feedID((const char*)pMessage);
        if (!feedID.empty()) {
            Feed::FeedDescription_s0061_1860* it = mMySporecasts.mpBegin;
            Feed::FeedDescription_s0061_1860* end = mMySporecasts.mpEnd;
            for (; it != end; ++it) {
                if (it->mFeedID == feedID)
                    break;
            }
            if (it != end)
                mMySporecasts.erase(it);
        }
        break;
    }
    case 0x3d1cd0b:
        if (pMessage)
            mMySubscriptions.push_back(*(Feed::FeedDescription_s0061_1860*)pMessage);
        break;
    case 0x3ffd8c9:
        if (pMessage) {
            eastl::string feedID((const char*)pMessage);
            if (!feedID.empty()) {
                Feed::FeedDescription_s0061_1860* it = mMySubscriptions.mpBegin;
                Feed::FeedDescription_s0061_1860* end = mMySubscriptions.mpEnd;
                for (; it != end; ++it) {
                    if (it->mFeedID == feedID)
                        break;
                }
                if (it != end)
                    mMySubscriptions.erase(it);
            }
        }
        break;
    case 0x457076f: {
        cSnapshotUploadMessage* pMsg = (cSnapshotUploadMessage*)pMessage;
        mTransactionQueue.Add(new Pollen::cSnapshotUploadTransaction_s0061_1860(pMsg->mKey, pMsg->mA.c_str(), pMsg->mB.c_str(), pMsg->mC.c_str(), pMsg->mD.c_str()), false);
        break;
    }
    case 0x45883b0:
        if (mbPollinationEnabled && !sAppProperties->mpData->mbOffline) {
            uint32_t assetID = *(uint32_t*)pMessage;
            uint32_t status = 5;
            UIntPair* it = mAssetStatus.find(assetID);
            if (it != mAssetStatus.end())
                status = it->second;
            mTransactionQueue.Add(new Pollen::cAssetStatusTransaction(0, assetID, status, 0), false);
        }
        break;
    case 0x46d05ee:
        if (mbPollinationEnabled) {
            ISporepediaQuery* pQuery = OnlineState()->mpQuery;
            if (pQuery && pQuery->GetCount() > 0) {
                pQuery->Reset(0, 0);
                mTransactionQueue.Add(new Pollen::cTransaction616660(pQuery, OnlineState()->mUserID), false);
            }
        }
        break;
    case 0x49a3777:
        if (pMessage) {
            Feed::FeedDescription_s0061_1860* pFeed = (Feed::FeedDescription_s0061_1860*)pMessage;
            Feed::FeedDescription_s0061_1860* it = mMySporecasts.mpBegin;
            Feed::FeedDescription_s0061_1860* end = mMySporecasts.mpEnd;
            for (; it != end; ++it) {
                if (it->mFeedID == pFeed->mFeedID)
                    break;
            }
            if (it != end)
                *it = *pFeed;
        }
        break;
    case 0x55be439: {
        cYouTubeAuthMessage* pMsg = (cYouTubeAuthMessage*)pMessage;
        mTransactionQueue.Add(new Pollen::cYouTubeAuthenticationTransaction_s0061_1860(pMsg->mA.c_str(), pMsg->mB.c_str(), pMsg->mC.c_str(), pMsg->mD), false);
        break;
    }
    case 0x55e8bc8: {
        cYouTubeUploadMessage* pMsg = (cYouTubeUploadMessage*)pMessage;
        mTransactionQueue.Add(new Pollen::cYouTubeVideoUploadTransaction_s0061_1860(pMsg->mA.c_str(), pMsg->mB.c_str(), pMsg->mC.c_str(), pMsg->mD.c_str(), pMsg->mE.c_str(), pMsg->mKey, pMsg->mF), false);
        break;
    }
    case 0x56cd8c4: {
        cYouTubeURLMessage* pMsg = (cYouTubeURLMessage*)pMessage;
        mTransactionQueue.Add(new Pollen::cYouTubeVideoURLTransaction_s0061_1860(pMsg->mA.c_str(), pMsg->mB.c_str(), pMsg->mC.c_str(), pMsg->mD.c_str()), false);
        break;
    }
    case 0x56d09b3: {
        IRequestMessage* pRequest = (IRequestMessage*)pMessage;
        IResponseCallback* pCallback = pRequest->GetCallback();
        cIntVariant v;
        v = pRequest->GetRequest()->GetValue(0);
        int value = *v.GetPtr();
        mbShutdownInProgress = value != 0;
        pCallback->Complete(0);
        break;
    }
    case 0x5d313c7:
        CancelTransactions(*(uint32_t*)pMessage);
        break;
    case 0x5fff3ff:
        if (mbPollinationEnabled && pMessage) {
            cPairMessage* pMsg = (cPairMessage*)pMessage;
            if (mTransactionQueue.Add(new Pollen::cTransaction6166e0(pMsg->mA, pMsg->mB), false))
                break;
        }
        MessageServer_s0061_1860()->PostMSG(0x60ba744, 0, 0);
        break;
    case 0x632d709: {
        UIntPair* it = mAssetStatus.mpBegin;
        UIntPair* end = mAssetStatus.mpEnd;
        for (; it != end; ++it)
            mTransactionQueue.Add(new Pollen::cAssetStatusTransaction(0, it->first, it->second, 0), false);
        break;
    }
    case 0x2ba2010:
    case 0x73e46f6:
    case 0x611a3f72:
        if (mbPollinationEnabled && !mbShutdownInProgress) {
            bool bA = messageID == 0x73e46f6;
            bool bB = messageID == 0x611a3f72;
            ResourceKey_s0061_1860 key = *(ResourceKey_s0061_1860*)pMessage;
            if (mPollinateRequests.insert(key).second) {
                if (mnNextAssetID == 0xffffffffffffffffULL)
                    mUploadQueue.push_back(cUploadRequest(key, bA, bB));
                else
                    HandlePollinateRequest(key, bA, bB);
            }
        }
        break;
    default:
        return true;
    }

    if (mbFlushQueue)
        mTransactionQueue.Clear();
    ProcessTransactionQueue();
    return true;
}
}  // namespace SP

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
