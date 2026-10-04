// Tail of EA::Internet::HTTPMultipartRelatedPostBodyStream, Pollinator (SP::cPollinator) helpers and a few
// EASTL deque / hashtable instances over AutoRefCount pointers.
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-  (no /EHsc)
#include "s0060c780.h"

extern "C" long __cdecl _InterlockedExchangeAdd(long volatile*, long);
#pragma intrinsic(_InterlockedExchangeAdd)

struct ListNodeBase {
  ListNodeBase* mpNext;
  ListNodeBase* mpPrev;
};

// ---------------------------------------------------------------------------------------------
// HTTP multipart related stream

namespace EA {
namespace IO {
class IStream {
 public:
  IStream() {}
  virtual ~IStream() {}
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
class MemoryStream : public IStream {
 public:
  MemoryStream(void* pData, uint32_t nSize, const char* pName);  // 0x0093c270
  char pad[0x24 - 4];
};
// A window onto part of another stream (class name guessed), 0x1c bytes.
class SubStream : public IStream {
 public:
  SubStream(IStream* pSource, uint32_t nStart, uint32_t nSize);  // 0x0093b7d0
  char pad[0x1c - 4];
};
}  // namespace IO
namespace COM {
template <typename T>
class RefCountTemplateA {
 public:
  virtual ~RefCountTemplateA() {}
  T mRefCount;
};
}  // namespace COM
}  // namespace EA

namespace EA {
namespace Internet {

class IHTTPPostBodyStream : public IO::IStream {
 public:
  virtual void pv3c();
  virtual bool GetContentTypeString(string8& sContentType);  // +0x40
  virtual bool Finalize();                                    // +0x44
  virtual bool SetBoundary(const char* pBoundary);            // +0x48
  virtual const char* GetBoundary() const;                    // +0x4c
  virtual bool AddFormData(const char* pName, const char* pValue);  // +0x54
  virtual bool AddFormData(const char* pName, IO::IStream* pStream, const char* pContentType,
                           const char* pFileName, const char* pTransferEncoding);  // +0x50
  virtual bool AddFormDataXML(const char* pXML);  // +0x58
  virtual bool AddFormDataVideo(const char* pContentType, const char* pTransferEncoding, IO::IStream* pStream);  // +0x5c
  virtual void WriteToStream(const char* pText, IO::IStream* pStream);  // +0x60
  virtual bool WriteEndBoundary();                                      // +0x64
  virtual bool CommitTextSegment();                                     // +0x68
};

struct IStreamNode : public ListNodeBase {
  IO::IStream* mpStream;
};
struct IStreamList {
  IStreamList() {
    mNode.mpNext = &mNode;
    mNode.mpPrev = &mNode;
  }
  ~IStreamList() { DoClear(); }
  ListNodeBase mNode;
  uint32_t mAllocator;
  void DoClear();  // 0x0060c4a0
};

template <typename T>
struct StreamRef {
  T* mpObject;
  StreamRef() : mpObject(0) {}
  StreamRef(T* p) : mpObject(p) {
    if (mpObject) mpObject->AddRef();
  }
  ~StreamRef() {
    if (mpObject) mpObject->Release();
  }
  StreamRef& operator=(T* p);  // 0x00572620
};

class HTTPMultipartRelatedPostBodyStream : public IHTTPPostBodyStream,
                                           public COM::RefCountTemplateA<Thread::AtomicInt<int> > {
 public:
  enum eFormDataType { kText = 0, kStream = 1 };
  virtual bool AddFormData(const char* pName, const char* pValue);
  virtual bool AddFormData(const char* pName, IO::IStream* pStream, const char* pContentType,
                           const char* pFileName, const char* pTransferEncoding);
  virtual bool AddFormDataVideo(const char* pContentType, const char* pTransferEncoding, IO::IStream* pStream);
  virtual bool CommitTextSegment();

  IStreamList mFormDataList;       // +0xc
  string8 msBoundary;              // +0x18
  IStreamNode* mReadItr;           // +0x28
  long mnPosition;                 // +0x2c
  unsigned int mnSize;             // +0x30
  int mnState;                     // +0x34
  bool mbFinal;                    // +0x38
  eFormDataType mLastDataType;     // +0x3c
  unsigned int mnTextStart;        // +0x40
  IO::MemoryStream* mpMemStream;   // +0x44
};

// @ 0x0060c780
bool HTTPMultipartRelatedPostBodyStream::AddFormData(const char* pName, IO::IStream* pStream,
                                                     const char* pContentType, const char* pFileName,
                                                     const char* pTransferEncoding) {
  if (mbFinal) mnState = -1;
  if (pName && pStream && pContentType) {
    const int nSize = (int)pStream->GetSize();
    if (nSize != -1 && nSize != -2) goto lOk;
  }
  mnState = -1;
lOk:
  if (mnState == 0) {
    const uint32_t nPosition = mpMemStream->GetPosition(0);
    if (mLastDataType == kStream) {
      mnTextStart = nPosition;
      mLastDataType = kText;
    }
    WriteToStream("\r\n--", mpMemStream);
    mpMemStream->Write(msBoundary.c_str(), msBoundary.size());
    WriteToStream("\r\nContent-Disposition: form-data; name=\"", mpMemStream);
    WriteToStream(pName, mpMemStream);
    WriteToStream("\"", mpMemStream);
    if (pFileName) {
      WriteToStream("; filename=\"", mpMemStream);
      WriteToStream(pFileName, mpMemStream);
      WriteToStream("\"", mpMemStream);
    }
    WriteToStream("\r\n", mpMemStream);
    WriteToStream("Content-Type: ", mpMemStream);
    WriteToStream(pContentType, mpMemStream);
    WriteToStream("\r\n", mpMemStream);
    if (pTransferEncoding) {
      WriteToStream("Content-Transfer-Encoding: ", mpMemStream);
      WriteToStream(pTransferEncoding, mpMemStream);
      WriteToStream("\r\n", mpMemStream);
    }
    WriteToStream("\r\n", mpMemStream);
    if (mpMemStream->GetState() == 0 && CommitTextSegment()) {
      StreamRef<IO::IStream> ref(pStream);
      IStreamNode* const pNode = (IStreamNode*)EASTL_allocator_allocate(sizeof(IStreamNode), "Editor", 0, 0, "EASTL/allocator.h", 0xd1);
      if (&pNode->mpStream) {
        pNode->mpStream = ref.mpObject;
        if (ref.mpObject) ref.mpObject->AddRef();
      }
      pNode->mpNext = &mFormDataList.mNode;
      pNode->mpPrev = mFormDataList.mNode.mpPrev;
      mFormDataList.mNode.mpPrev->mpNext = pNode;
      mFormDataList.mNode.mpPrev = pNode;
      mnSize += pStream->GetAvailable();
      mLastDataType = kStream;
      return true;
    }
    mnState = -1;
  }
  return false;
}

// @ 0x0060c9c0
bool HTTPMultipartRelatedPostBodyStream::AddFormDataVideo(const char* pContentType, const char* pTransferEncoding,
                                                          IO::IStream* pStream) {
  if (mbFinal) mnState = -1;
  if (pContentType && pTransferEncoding && pStream) {
    const int nSize = (int)pStream->GetSize();
    if (nSize != -1 && nSize != -2) goto lOk;
  }
  mnState = -1;
lOk:
  if (mnState == 0) {
    const uint32_t nPosition = mpMemStream->GetPosition(0);
    if (mLastDataType == kStream) {
      mnTextStart = nPosition;
      mLastDataType = kText;
    }
    WriteToStream("\r\n--", mpMemStream);
    mpMemStream->Write(msBoundary.c_str(), msBoundary.size());
    WriteToStream("\r\n", mpMemStream);
    WriteToStream("Content-Type: ", mpMemStream);
    WriteToStream(pContentType, mpMemStream);
    WriteToStream("\r\n", mpMemStream);
    WriteToStream("Content-Transfer-Encoding: ", mpMemStream);
    WriteToStream(pTransferEncoding, mpMemStream);
    WriteToStream("\r\n", mpMemStream);
    WriteToStream("\r\n", mpMemStream);
    if (mpMemStream->GetState() == 0 && CommitTextSegment()) {
      StreamRef<IO::IStream> ref(pStream);
      IStreamNode* const pNode = (IStreamNode*)EASTL_allocator_allocate(sizeof(IStreamNode), "Editor", 0, 0, "EASTL/allocator.h", 0xd1);
      if (&pNode->mpStream) {
        pNode->mpStream = ref.mpObject;
        if (ref.mpObject) ref.mpObject->AddRef();
      }
      pNode->mpNext = &mFormDataList.mNode;
      pNode->mpPrev = mFormDataList.mNode.mpPrev;
      mFormDataList.mNode.mpPrev->mpNext = pNode;
      mFormDataList.mNode.mpPrev = pNode;
      mnSize += pStream->GetAvailable();
      mLastDataType = kStream;
      return true;
    }
    mnState = -1;
  }
  return false;
}

// @ 0x0060cb90
bool HTTPMultipartRelatedPostBodyStream::CommitTextSegment() {
  if (!mbFinal && mpMemStream && mLastDataType == kText) {
    StreamRef<IO::IStream> pSegment;
    void* const pMem = operator new(0x1c, "Pollinator", 0, 0, 0, 0);
    IO::SubStream* pSub = 0;
    if (pMem) pSub = new (pMem) IO::SubStream(mpMemStream, mnTextStart, mpMemStream->GetPosition(0) - mnTextStart);
    pSegment = pSub;
    if (pSegment.mpObject) {
      pSegment.mpObject->SetPosition(0, 0);
      StreamRef<IO::IStream> pTemp(pSegment.mpObject);
      IStreamNode* const pNode = (IStreamNode*)EASTL_allocator_allocate(sizeof(IStreamNode), "Editor", 0, 0, "EASTL/allocator.h", 0xd1);
      if (&pNode->mpStream) {
        pNode->mpStream = pTemp.mpObject;
        if (pTemp.mpObject) pTemp.mpObject->AddRef();
      }
      pNode->mpNext = &mFormDataList.mNode;
      pNode->mpPrev = mFormDataList.mNode.mpPrev;
      mFormDataList.mNode.mpPrev->mpNext = pNode;
      mFormDataList.mNode.mpPrev = pNode;
      mnSize += mpMemStream->GetPosition(0) - mnTextStart;
      mnTextStart = mpMemStream->GetPosition(0);
      return true;
    }
  }
  mnState = -1;
  return false;
}

}  // namespace Internet
}  // namespace EA

// ---------------------------------------------------------------------------------------------
// Pollinator helpers

namespace SP {

struct ResourceKey {
  uint32_t instanceID;
  uint32_t typeID;
  uint32_t groupID;
};

// Upload queue entry: a resource key plus two flags (class name guessed).
struct UploadEntry {
  ResourceKey mKey;
  bool mbFlag0;  // +0xc
  bool mbFlag1;  // +0xd
  UploadEntry(const ResourceKey& key, bool bFlag0, bool bFlag1);
  UploadEntry(const UploadEntry& x) : mKey(x.mKey), mbFlag0(x.mbFlag0), mbFlag1(x.mbFlag1) {}
};

// @ 0x0060ccc0
UploadEntry::UploadEntry(const ResourceKey& key, bool bFlag0, bool bFlag1) : mKey(key), mbFlag0(bFlag0), mbFlag1(bFlag1) {}

uint32_t FNV1(const char* pName, uint32_t nInitial, int bLowerCase);  // 0x00932e80

// @ 0x0060ccf0
bool GetTypeFromName(const char* pName, uint32_t* pType) {
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

struct cAchievementSource {
  char pad[0x43c];
  int mnID;  // +0x43c
};

// @ 0x0060ce10
int ClassifyCommand(short nCommand, cAchievementSource* pSource) {
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

class cPollinator {
 public:
  void SetEnabledState(int nState);
  char pad[0xb0];
  bool mbShutdownInProgress;  // +0xb0
  char pad2[0x40];
  bool mbPollinationEnabled;  // +0xf1 (retail layout; +0xb1 in the 2008 PDB)
};

// @ 0x0060cec0
void cPollinator::SetEnabledState(int nState) {
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

struct cAchievementsController {
  void AutoTest(uint32_t nAchievementID, int);  // 0x00676e90
};
cAchievementsController* GetAchievementsController();  // 0x00675250
struct cGameEventMessage {
  uint32_t pad0;
  uint32_t mnEventID;  // +0x4
};

// @ 0x0060cf30
void __stdcall OnGameEvent(cGameEventMessage* pMessage) {
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

// @ 0x0060d1e0
void __stdcall SendNotificationMessage(void*) { MessageServer()->MessageSend(0x6299932, 0, 0); }

}  // namespace SP

// @ 0x0060cfa0
struct VariantHelper {
  uint64_t mUint64;       // +0x0
  uint32_t pad8[2];
  uint16_t mFlags;        // +0x10
  uint16_t mTypeId;       // +0x12
  VariantHelper& operator=(const uint64_t& value);
  void Destruct(int);                                                       // 0x0093db80
  void Assign(int typeId, int, const void* pValue, int nSize, int bCopy);   // 0x0093dd80
};
VariantHelper& VariantHelper::operator=(const uint64_t& value) {
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

// ---------------------------------------------------------------------------------------------
// EASTL deque / hashtable instances over AutoRefCount pointers

// A deque<AutoRefCount<T>> with 64-element subarrays (0x100 bytes per subarray).
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

// @ 0x0060d000  (finds the listener with the given ID and notifies it)
struct ListenerQuery {
  int mnID;
  void* mpData;
};
ListenerIterator FindAndNotify(ListenerIterator first, ListenerIterator last, ListenerQuery query) {
  for (; first.mpCurrent != last.mpCurrent; ++first) {
    IListener* const pListener = *first.mpCurrent;
    if (pListener->GetID() == query.mnID) {
      pListener->Notify(8, 0, query.mpData);
      break;
    }
  }
  return first;
}

// @ 0x0060d0a0  (notifies the first listener that is ready)
ListenerIterator FindReadyAndNotify(ListenerIterator first, ListenerIterator last, void* pData) {
  for (; first.mpCurrent != last.mpCurrent; ++first) {
    IListener* const pListener = *first.mpCurrent;
    if (pListener->IsReady()) {
      pListener->Notify(8, 0, pData);
      break;
    }
  }
  return first;
}

namespace SP {
// @ 0x0060d140
UploadEntry* uninitialized_copy_entries(const UploadEntry* first, const UploadEntry* last, UploadEntry* dest) {
  for (; first != last; ++first, ++dest) ::new (dest) UploadEntry(*first);
  return dest;
}
}  // namespace SP

// A deque<AutoRefCount<EA::IO::IStream>>.
namespace StreamDeque {
using EA::IO::IStream;
struct StreamPtr {
  IStream* mpObject;
  ~StreamPtr() {
    if (mpObject) mpObject->Release();
  }
  StreamPtr& operator=(const StreamPtr& x) {
    IStream* const pObject = x.mpObject;
    IStream* const pTemp = mpObject;
    if (pObject != pTemp) {
      if (pObject) pObject->AddRef();
      mpObject = pObject;
      if (pTemp) pTemp->Release();
    }
    return *this;
  }
};
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

// @ 0x0060d610
Iterator copy(Iterator first, Iterator last, Iterator result) {
  while (first.mpCurrent != last.mpCurrent) {
    *result.mpCurrent = *first.mpCurrent;
    ++result;
    ++first;
  }
  return result;
}

// @ 0x0060d6e0
Iterator copy_backward(Iterator first, Iterator last, Iterator resultEnd) {
  while (last.mpCurrent != first.mpCurrent) {
    --last;
    --resultEnd;
    *resultEnd.mpCurrent = *last.mpCurrent;
  }
  return resultEnd;
}

enum Side { kSideFront, kSideBack };
template <typename T>
inline const T& max_alt(const T& a, const T& b) { return a < b ? b : a; }
#define USED_PTR_SPACE ((unsigned int)((char*)mItEnd.mpCurrentArrayPtr - (char*)mItBegin.mpCurrentArrayPtr) + sizeof(void*))

extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
extern "C" __declspec(dllimport) void* __cdecl memmove(void*, const void*, unsigned int);

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

// @ 0x0060d2e0
void DequeBase::clear() {
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

// @ 0x0060d3c0
void DequeBase::DoReallocPtrArray(unsigned int nAdditionalCapacity, Side allocationSide) {
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

// ---------------------------------------------------------------------------------------------
// Atomic AutoRefCount helpers, hashtable distance, job result message

namespace SP {

// EA::RefCountTemplate<AtomicInt<int>>-style object: vptr at +0, atomic count at +4.
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

struct AtomicRef {
  AtomicRefCounted* mpObject;
  ~AtomicRef();   // 0x0060d210
  AtomicRef& reset();  // 0x0060d240
};

// @ 0x0060d210
AtomicRef::~AtomicRef() {
  if (mpObject) mpObject->Release();
}

// @ 0x0060d240
AtomicRef& AtomicRef::reset() {
  AtomicRefCounted* const p = mpObject;
  if (p) {
    mpObject = 0;
    p->Release();
  }
  return *this;
}

// hashtable_iterator: node {value[8], next} and a bucket pointer.
struct HashNode {
  uint32_t mValue[2];
  HashNode* mpNext;  // +0x8
};
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

// @ 0x0060d5d0
int distance(HashIterator first, HashIterator last) {
  int n = 0;
  while (first.mpNode != last.mpNode) {
    ++first;
    ++n;
  }
  return n;
}

}  // namespace SP

namespace Pollinator {

class __declspec(novtable) IMessageBase {
 public:
  virtual void m0() = 0;
};
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

class cJobResultMessage : public IMessageBase, public DefaultRefCounted {
 public:
  cJobResultMessage(uint32_t nJobID, uint32_t nResult, SP::AtomicRefCounted* pData);
  virtual void m0();
  virtual void d0();
  uint32_t mnJobID;                   // +0xc
  uint32_t mnResult;                  // +0x10
  SP::AtomicRefCounted* mpData;       // +0x14
};

// @ 0x0060d7a0
cJobResultMessage::cJobResultMessage(uint32_t nJobID, uint32_t nResult, SP::AtomicRefCounted* pData)
    : mnJobID(nJobID), mnResult(nResult), mpData(pData) {
  if (pData) pData->AddRef();
}

}  // namespace Pollinator

class IMessagingServer {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5)
  virtual void Post(const void* pMessageType, void* pMessage, int, int);  // +0x18
};
IMessagingServer* GetMessagingServer();  // 0x00883860
extern const char kJobResultMessageType[];  // 0x0164d214

// @ 0x0060d800
void NotificationFunction(void*, void*, uint32_t nMessage, uint32_t* pData) {
  if (nMessage == 0x700af301) {
    IMessagingServer* const pServer = GetMessagingServer();
    void* const pMem = operator new(0x18, "Pollinator/cJobResultMessage", 0, 0, 0, 0);
    Pollinator::cJobResultMessage* const pMessage =
        pMem ? new (pMem) Pollinator::cJobResultMessage(pData[0], pData[1], (SP::AtomicRefCounted*)pData[9]) : 0;
    pServer->Post(kJobResultMessageType, pMessage, 0, 0);
  }
}

namespace SP {
struct cCommandBase {
  ~cCommandBase();  // 0x0083c750
  char pad[0x10];
};
extern void* gPaintSystemVtbl[];  // 0x013eb394

class cPollinatorCheat : public cCommandBase {
 public:
  cPollinatorCheat* DeletingDtor(unsigned char flags);
  void* mpVtbl10;  // +0x10
};

// @ 0x0060d1b0
cPollinatorCheat* cPollinatorCheat::DeletingDtor(unsigned char flags) {
  mpVtbl10 = gPaintSystemVtbl;
  cCommandBase::~cCommandBase();
  if (flags & 1) EASTL_allocator_deallocate(this);
  return this;
}
}  // namespace SP
