// Slice s007eb430: SP::cTelemetry (telemetry subsystem) and the EASTL
// list / hashtable / vector primitives it instantiates.
// Flags: /O2 /MD /Gy /EHsc /TP.
#include "types.h"

// ---------------------------------------------------------------------------
// allocator plumbing (masked relocations).
void* operator new[](size_t size, const char* pName, int flags, unsigned debugFlags,
                     const char* file, int line); // 0x00f473a0
void* operator new(size_t size, const char* pName, int flags, unsigned debugFlags,
                   const char* file, int line);
void operator delete(void* p); // 0x00f47380
void operator delete[](void* p);
inline void* operator new(size_t, void* p) throw() { return p; }

#define ALLOC_FILE "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h"

inline void* EAAlloc(size_t n) { return operator new[](n, "App", 0, 0, ALLOC_FILE, 0xd1); }

namespace EA {
namespace DateTime {
class DateTime {
 public:
  int64_t mnSeconds;  // +0x0
  void Set(int kind);  // 0x0092e3d0
};
}  // namespace DateTime
namespace COM {
class IRefCount {
 public:
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
};
class IUnknown32 : public IRefCount {
 public:
  virtual void v4();
  virtual void v5();
};
}  // namespace COM

namespace IO {
class IStream {
 public:
  virtual void v00();     // +0x0
  virtual int AddRef();   // +0x4
  virtual int Release();  // +0x8
  virtual void v03();     // +0xc
  virtual void v04();     // +0x10
  virtual void v05();     // +0x14
  virtual void v06();     // +0x18
  virtual uint32_t v07(); // +0x1c  byte count
  virtual void v08();     // +0x20
  virtual void v09();     // +0x24
  virtual void v10(int a, int b);  // +0x28
  virtual void v11();     // +0x2c
};
class MemoryStream : public IStream {
 public:
  void* mpSharedPointer;  // +0x4
  int mnRefCount;         // +0x8
  uint32_t mnSize;        // +0xc
  uint32_t mnCapacity;    // +0x10
  uint32_t mnPosition;    // +0x14
  bool mbResizeEnabled;   // +0x18
  float mfResizeFactor;   // +0x1c
  int mnResizeIncrement;  // +0x20
  void Init(const char* name);       // 0x0093bd50
  void SetOption(int opt, float v);  // 0x0093bb40
  void* GetData() const;             // 0x0093ba70
};
class FileStream {
 public:
  FileStream(const wchar_t* path);                  // 0x00931e10
  ~FileStream();                                    // 0x00931e70
  bool Open(uint32_t a, int b, uint32_t c, int d);  // 0x009318f0
  bool SetPosition(int a, int b);                   // 0x00931c70
  bool Write(const void* p, uint32_t n);            // 0x00931d30
  bool Close();                                     // 0x00931a70
 private:
  char mStorage[0x22c];  // EA::IO::FileStream object body
};
}  // namespace IO
namespace Messaging {
class IServer {
 public:
  virtual void v00();
  virtual void v01();
  virtual void v02();
  virtual void v03();
  virtual void v04();
  virtual void v05(uint32_t id, void* msg, int flags);  // +0x14
};
IServer* GetServer();  // 0x00883860
}  // namespace Messaging

template <class T>
class RefCountTemplate {
 public:
  T mRefCount;  // +0x4
  RefCountTemplate() : mRefCount(0) {}
  virtual ~RefCountTemplate() {}
};

template <class T>
class AutoRefCount {
 public:
  T* mpObject;  // +0x0
  AutoRefCount(T* p = 0) : mpObject(p) {}
  ~AutoRefCount() {
    if (mpObject) mpObject->Release();
  }
};
}  // namespace EA

namespace SP {
class cISerializableObject : public EA::COM::IUnknown32 {};

struct TDataVec {
  float* mpBegin;        // +0x0
  float* mpEnd;          // +0x4
  float* mpCapacity;     // +0x8
  const char* mpName;    // +0xc
  uint32_t mFlags;       // +0x10
  TDataVec() {}
  TDataVec(const TDataVec& x);  // 0x007EB360
  ~TDataVec();                  // 0x007EB3F0
};  // size 0x14

class cTelemetryItem { public:
  EA::DateTime::DateTime mSystemTime;  // +0x0
  uint32_t mType;                      // +0x8
  TDataVec mData;                      // +0xc
};  // size 0x20

struct TItemListNode {
  TItemListNode* mpNext;  // +0x0
  TItemListNode* mpPrev;  // +0x4
  cTelemetryItem mValue;  // +0x8
};
struct TItemList {
  TItemListNode* mpNext;  // +0x0 sentinel next
  TItemListNode* mpPrev;  // +0x4 sentinel prev
  uint32_t mnSize;        // +0x8
  TItemList();
  TItemList(const TItemList& x);
  ~TItemList();
  __declspec(noinline) TItemListNode* AllocNode(const cTelemetryItem& value);
  void CopyRange(TItemListNode* first, TItemListNode* last, TItemList* dst);
};
struct TItemMapNode {
  uint32_t mKey;         // +0x0
  TItemList mList;       // +0x4
  TItemMapNode* mpNext;  // +0x10
};  // size 0x14
struct TItemMap {
  uint32_t mHash;               // +0x0
  TItemMapNode** mpBucketArray; // +0x4
  uint32_t mnBucketCount;       // +0x8
  uint32_t mnElementCount;      // +0xc
  float mfMaxLoadFactor;        // +0x10
  float mfGrowthFactor;         // +0x14
  uint32_t mnNextResize;        // +0x18
  uint32_t mAllocator;          // +0x1c
  void DoFreeNodes(TItemMapNode** bucketArray, uint32_t n);
  uint32_t erase(const uint32_t& key);
  TItemList* operator[](const uint32_t& key);
};  // size 0x20
extern TItemMapNode* gEmptyBucketArray;  // 0x0154DF28

// A plain EASTL-style vector<int> (allocator is stateless).
struct IntVector {
  int* mpBegin;   // +0x0
  int* mpEnd;     // +0x4
  int* mpCapacity;  // +0x8
  void DoInsertValues(int* position, uint32_t n, const int& value);  // 0x007EB430
  void resize(uint32_t n);                                           // 0x007EB820
};

class cTelemetry : public EA::RefCountTemplate<int>, public cISerializableObject {
 public:
  TItemMap mStats;                          // +0xc
  int64_t mSession;                         // +0x30
  bool mbFileDump;                          // +0x38
  EA::AutoRefCount<EA::IO::MemoryStream> mpStream;  // +0x3c

  cTelemetry();                        // 0x007EC0A0
  void FileDump();                     // 0x007EB600
  void PrepareFlush(uint32_t a, uint32_t b);  // 0x007EBBA0
  void Reset(int id);                  // 0x007EBB60
  __declspec(noinline) void Flush(uint32_t id);          // 0x007EBCE0
  ~cTelemetry();                       // 0x007EBE70
  bool Shutdown();                     // 0x007EBF90
  void Add(const uint32_t& key, const uint32_t& value);  // 0x007EC160
};
}  // namespace SP

namespace {
using namespace SP;
}  // namespace

// ---------------------------------------------------------------------------
// callees that live outside this slice (each annotated with its address)
// ---------------------------------------------------------------------------
struct WString16 {                   // eastl::basic_string<wchar_t>
  wchar_t* mpBegin;                  // +0x0
  wchar_t* mpEnd;                    // +0x4
  wchar_t* mpCapacity;               // +0x8
  WString16() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  ~WString16() {
    if (mpBegin && ((int)((char*)mpCapacity - (char*)mpBegin) & ~1) > 2)
      operator delete(mpBegin);
  }
  void RangeInitialize(const wchar_t* p);  // 0x00579a90
};
void WstrFormat(void* s, const wchar_t* fmt, ...);  // 0x004e0850
const wchar_t* GetBasePath();                       // 0x00688cf0
extern const wchar_t DAT_0141428c[];                // 0x0141428c  L"telemetry.dat"
extern const wchar_t DAT_014142a8[];                // 0x014142a8  session format
extern void* const g_vtbl_013eb90c;                 // 0x013eb90c
extern void* const g_vtbl_013eb844;                 // 0x013eb844

struct ObjB0 {                // cTelemetry as a hashtable holder
  char mPad[0x10];            // +0x0  (mStats up to its bucket array)
  uint32_t FUN_007eb090();    // 0x007eb090  item count
};

bool WriteUint32(uint32_t stream, const void* p, int count, int flags);  // 0x0093aa70
bool WriteUint64(uint32_t stream, const void* p, int count, int flags);  // 0x0093ab10

struct MessageBasicRC5 {      // EA::Messaging::MessageBasicRC<5>
  void* mpVtbl;               // +0x0
  uint32_t mRefCount;         // +0x4
  char mPad08[0x28];          // +0x8
  uint32_t mField30;          // +0x30
  char mPad34[4];             // +0x34
  uint32_t mField38;          // +0x38
  void Destruct();            // 0x00421cf0
};

// ---------------------------------------------------------------------------
// @ 0x007EB430  IntVector::DoInsertValues
void SP::IntVector::DoInsertValues(int* position, uint32_t n, const int& value) {
  uint32_t nPosition = (uint32_t)(position - mpBegin);
  uint32_t nElementCount = (uint32_t)(mpEnd - mpBegin);
  if ((uint32_t)(mpCapacity - mpEnd) >> 2 >= n) {
    // enough room at the end
    uint32_t nElementsAfter = nElementCount - nPosition;
    if (nElementsAfter < n) {
      int* pOldEnd = mpEnd;
      uint32_t nU = n - nElementsAfter;
      mpEnd = mpEnd + (n - nElementsAfter);
      for (uint32_t i = 0; i < nU; ++i) pOldEnd[i] = value;
      // move existing tail
      int* pDst = mpEnd;
      for (uint32_t i = 0; i < nElementsAfter; ++i) pDst[i] = position[i];
      for (uint32_t i = 0; i < nElementsAfter; ++i) position[i] = value;
      return;
    }
    int* pOldEnd = mpEnd;
    int* pNewEnd = position + n;
    uint32_t nMove = nElementsAfter - n;
    for (uint32_t i = nMove; i > 0; --i) pOldEnd[i - 1 + n] = pOldEnd[i - 1];
    for (uint32_t i = 0; i < n; ++i) position[i] = value;
    mpEnd = pOldEnd + n;
    return;
  }
  // reallocate
  uint32_t nOldCapacity = (uint32_t)(mpCapacity - mpBegin);
  uint32_t nNewCapacity = nOldCapacity + (nOldCapacity >> 1);
  if (nNewCapacity < nElementCount + n) nNewCapacity = nElementCount + n;
  int* pNewData = nNewCapacity ? (int*)EAAlloc(nNewCapacity * 4) : 0;
  int* pDst = pNewData;
  for (int* p = mpBegin; p != position; ++p) *pDst++ = *p;
  for (uint32_t i = 0; i < n; ++i) *pDst++ = value;
  for (int* p = position; p != mpEnd; ++p) *pDst++ = *p;
  if (mpBegin && *(uint32_t*)((char*)mpBegin - 4)) operator delete(mpBegin);
  mpBegin = pNewData;
  mpEnd = pDst;
  mpCapacity = pNewData + nNewCapacity;
}

// @ 0x007EB820  IntVector::resize
void SP::IntVector::resize(uint32_t n) {
  uint32_t cur = (uint32_t)(mpEnd - mpBegin);
  if ((uint32_t)(mpCapacity - mpBegin) < n) {
    int zero = 0;
    DoInsertValues(mpEnd, n - cur, zero);
  } else {
    // erase tail (FUN_007EB3B0)
    extern void IntVecEraseRange(int* first, int* last);
    IntVecEraseRange(mpBegin + n, mpEnd);
  }
}

// @ 0x007EB720  TItemList::AllocNode
SP::TItemListNode* SP::TItemList::AllocNode(const cTelemetryItem& value) {
  TItemListNode* pNode = (TItemListNode*)EAAlloc(sizeof(TItemListNode));
  if (pNode) pNode->mValue = value;
  return pNode;
}

// @ 0x007EB7D0  TItemList::CopyRange
void SP::TItemList::CopyRange(TItemListNode* first, TItemListNode* last, TItemList* dst) {
  for (; first != last; first = first->mpNext) {
    TItemListNode* pNode = dst->AllocNode(first->mValue);
    pNode->mpNext = dst->mpNext;
    pNode->mpPrev = (TItemListNode*)dst;
    dst->mpNext->mpPrev = pNode;
    dst->mpNext = pNode;
    ++dst->mnSize;
  }
}

// @ 0x007EB870  TItemList::TItemList(const TItemList&)
SP::TItemList::TItemList(const TItemList& x) {
  mpNext = (TItemListNode*)this;
  mpPrev = (TItemListNode*)this;
  mnSize = 0;
  extern void ListCopyRange(TItemList* dst, TItemListNode* first, TItemListNode* last);
  ListCopyRange(this, x.mpNext, (TItemListNode*)&x);
}

// @ 0x007EB8D0  make a TItemMapNode
extern "C" SP::TItemMapNode* MakeItemMapNode(const uint32_t* pKey) {
  SP::TItemMapNode* pNode = (SP::TItemMapNode*)EAAlloc(sizeof(SP::TItemMapNode));
  if (pNode) {
    pNode->mKey = *pKey;
    new (&pNode->mList) SP::TItemList();
  }
  pNode->mpNext = 0;
  return pNode;
}

// @ 0x007EB950  TItemMap::DoFreeNodes
void SP::TItemMap::DoFreeNodes(TItemMapNode** bucketArray, uint32_t n) {
  for (uint32_t i = 0; i < n; ++i) {
    TItemMapNode* pNode = bucketArray[i];
    while (pNode) {
      TItemMapNode* pNext = pNode->mpNext;
      pNode->mList.~TItemList();
      operator delete(pNode);
      pNode = pNext;
    }
    bucketArray[i] = 0;
  }
}

// @ 0x007EB9E0  TItemMap::erase
uint32_t SP::TItemMap::erase(const uint32_t& key) {
  uint32_t nElementCountSaved = mnElementCount;
  uint32_t n = key % mnBucketCount;
  TItemMapNode** pBucket = mpBucketArray + n;
  while (*pBucket && key != (*pBucket)->mKey) pBucket = &(*pBucket)->mpNext;
  while (*pBucket && key == (*pBucket)->mKey) {
    TItemMapNode* pNode = *pBucket;
    *pBucket = pNode->mpNext;
    pNode->mList.~TItemList();
    operator delete(pNode);
    --mnElementCount;
  }
  return nElementCountSaved - mnElementCount;
}

// @ 0x007EBBA0  cTelemetry::PrepareFlush
void SP::cTelemetry::PrepareFlush(uint32_t stream, uint32_t id) {
  for (uint32_t k = 0; k <= 6; ++k) {
    if (id != 0xffffffff && k != id) continue;
    uint32_t nBucketCount = mStats.mnBucketCount;
    TItemMapNode** pBuckets = mStats.mpBucketArray;
    uint32_t nBucket = k % nBucketCount;
    TItemMapNode* pNode = pBuckets[nBucket];
    while (pNode && pNode->mKey != k) pNode = pNode->mpNext;
    TItemMapNode** pIt = pBuckets + nBucket;
    TItemMapNode* pFound = pNode;
    if (!pNode) {
      pIt = pBuckets + nBucketCount;
      pFound = pBuckets[nBucketCount];
    }
    if (pFound != pBuckets[mStats.mnBucketCount]) {
      TItemList* pList = (TItemList*)((char*)pFound + 4);
      for (TItemListNode* p = pList->mpNext; p != (TItemListNode*)pList; p = p->mpNext) {
        int64_t t = p->mValue.mSystemTime.mnSeconds;
        WriteUint64(stream, &t, 1, 0);
        uint32_t key = k;
        WriteUint32(stream, &key, 1, 0);
        uint32_t type = p->mValue.mType;
        WriteUint32(stream, &type, 1, 0);
        uint32_t nCount = (uint32_t)(p->mValue.mData.mpEnd - p->mValue.mData.mpBegin);
        WriteUint32(stream, p->mValue.mData.mpBegin, nCount, 0);
      }
    }
    if (k == 0xffffffff) {
      mStats.DoFreeNodes(mStats.mpBucketArray, mStats.mnBucketCount);
      mStats.mnElementCount = 0;
    } else {
      mStats.erase(k);
    }
  }
}

// @ 0x007EBB60  cTelemetry::Reset
void SP::cTelemetry::Reset(int id) {
  if (id == -1) {
    TItemMap* m = &mStats;
    m->DoFreeNodes(m->mpBucketArray, m->mnBucketCount);
    m->mnElementCount = 0;
  } else {
    mStats.erase(*(uint32_t*)&id);
  }
}

// @ 0x007EBCE0  cTelemetry::Flush
void SP::cTelemetry::Flush(uint32_t id) {
  if (id == 0xffffffff || id < 7) {
    EA::IO::MemoryStream* pNew =
        (EA::IO::MemoryStream*)operator new[](0x24, "App", 0, 0, 0, 0);
    if (pNew) pNew->Init("App/Telemetry");
    EA::IO::MemoryStream* pOld = mpStream.mpObject;
    if (pNew != pOld) {
      if (pNew) pNew->AddRef();
      mpStream.mpObject = pNew;
      if (pOld) pOld->Release();
    }
    mpStream.mpObject->SetOption(1, 1.0f);
    mpStream.mpObject->SetOption(2, 2.0f);
    mpStream.mpObject->v10(0, 0);
    PrepareFlush((uint32_t)(size_t)mpStream.mpObject, id);
    FileDump();
    MessageBasicRC5 msg;
    msg.mField30 = 0;
    msg.mpVtbl = (void*)&g_vtbl_013eb90c;
    msg.mRefCount = 0;
    msg.mpVtbl = (void*)&g_vtbl_013eb844;
    msg.mField38 = 0;
    EA::Messaging::GetServer()->v05(0x46d05ee, &msg, 0);
    if (mpStream.mpObject) {
      EA::IO::MemoryStream* p = mpStream.mpObject;
      mpStream.mpObject = 0;
      p->Release();
    }
    msg.Destruct();
  }
}

// @ 0x007EBE70  cTelemetry::~cTelemetry
SP::cTelemetry::~cTelemetry() {
  mpStream.~AutoRefCount<EA::IO::MemoryStream>();
  mStats.DoFreeNodes(mStats.mpBucketArray, mStats.mnBucketCount);
  uint32_t nBucketCount = mStats.mnBucketCount;
  mStats.mnElementCount = 0;
  if (nBucketCount > 1) operator delete(mStats.mpBucketArray);
}

// @ 0x007EBF20  RefCountTemplate<int>::Release on the secondary subobject
int __fastcall TelemetryRelease(int* p) {
  int n = p[-1];
  p = p - 2;
  n += -1;
  p[1] = n;
  if (n == 0) {
    p[1] = 1;
    ((void(__thiscall*)(void*, int))(*(void***)p)[0])(p, 1);
    return 0;
  }
  return n;
}

// @ 0x007EBF90  cTelemetry::Shutdown
bool SP::cTelemetry::Shutdown() {
  TItemMap* m = &mStats;
  m->DoFreeNodes(m->mpBucketArray, m->mnBucketCount);
  m->mnElementCount = 0;
  EA::IO::MemoryStream* p = mpStream.mpObject;
  if (p) {
    mpStream.mpObject = 0;
    p->Release();
  }
  return true;
}

// @ 0x007EBFD0  TItemMap::operator[]
SP::TItemList* SP::TItemMap::operator[](const uint32_t& key) {
  extern void MapFind(TItemList** out, const uint32_t* key, TItemMap* self);  // 0x00DB4780
  TItemList* pFound;
  MapFind(&pFound, &key, this);
  if ((void*)pFound != (void*)mpBucketArray[mnBucketCount]) return pFound;
  TItemMapNode* pNode = (TItemMapNode*)EAAlloc(sizeof(TItemMapNode));
  pNode->mKey = key;
  new (&pNode->mList) TItemList();
  // insert at head of bucket
  uint32_t n = key % mnBucketCount;
  pNode->mpNext = mpBucketArray[n];
  mpBucketArray[n] = pNode;
  ++mnElementCount;
  return &pNode->mList;
}

// @ 0x007EC0A0  cTelemetry::cTelemetry
SP::cTelemetry::cTelemetry()
    : mSession(0), mbFileDump(false), mpStream(0) {
  mStats.mfMaxLoadFactor = 1.0f;
  mStats.mfGrowthFactor = 2.0f;
  mStats.mnNextResize = 0;
  mStats.mpBucketArray = (TItemMapNode**)&gEmptyBucketArray;
  mStats.mnBucketCount = 1;
  mStats.mnElementCount = 0;
}

// @ 0x007EB600  cTelemetry::FileDump
void SP::cTelemetry::FileDump() {
  if (!mbFileDump) return;
  WString16 path;
  path.RangeInitialize(GetBasePath());
  WstrFormat(&path, DAT_014142a8, mSession);
  WstrFormat(&path, DAT_0141428c);
  EA::IO::FileStream fs(path.mpBegin);
  if (fs.Open(3, 4, 1, 0)) {
    fs.SetPosition(0, 2);
    uint32_t nSize = mpStream.mpObject->v07();
    fs.Write(mpStream.mpObject->GetData(), nSize);
    fs.Close();
  }
}

// @ 0x007EC160  cTelemetry::Add
void SP::cTelemetry::Add(const uint32_t& key, const uint32_t& value) {
  if (0x2800 < (uint32_t)(((ObjB0*)this)->FUN_007eb090() * 0x20)) Flush(0xffffffff);
  TItemList* pList = mStats[key];
  cTelemetryItem item;
  item.mSystemTime.Set(2);
  item.mData.mpBegin = 0;
  item.mData.mpEnd = 0;
  item.mData.mpCapacity = 0;
  TItemListNode* pNode = pList->AllocNode(item);
  pNode->mpNext = (TItemListNode*)pList;
  pNode->mpPrev = pList->mpPrev;
  pList->mpPrev->mpNext = pNode;
  pList->mpPrev = pNode;
  pNode->mValue.mType = value;
}

// ---------------------------------------------------------------------------
// Out-of-line EASTL helpers that live at other addresses; declared here so the
// bodies above stay complete without pulling in their (unrelated) sources.
namespace SP {
// TDataVec copy ctor / dtor
TDataVec::TDataVec(const TDataVec& x) {
  mpBegin = 0;
  mpEnd = 0;
  mpCapacity = 0;
  if (x.mpBegin != x.mpEnd) {
    uint32_t n = (uint32_t)(x.mpEnd - x.mpBegin);
    mpBegin = (float*)EAAlloc(n * 4);
    mpEnd = mpBegin + n;
    mpCapacity = mpEnd;
    for (uint32_t i = 0; i < n; ++i) mpBegin[i] = x.mpBegin[i];
  }
  mpName = x.mpName;
  mFlags = x.mFlags;
}
TDataVec::~TDataVec() {
  if (mpBegin && *(uint32_t*)((char*)mpBegin - 4)) operator delete(mpBegin);
  mpBegin = 0;
  mpEnd = 0;
  mpCapacity = 0;
}
TItemList::TItemList() {
  mpNext = (TItemListNode*)this;
  mpPrev = (TItemListNode*)this;
  mnSize = 0;
}
TItemList::~TItemList() {
  TItemListNode* p = mpNext;
  while (p != (TItemListNode*)this) {
    TItemListNode* pNext = p->mpNext;
    p->~TItemListNode();
    operator delete(p);
    p = pNext;
  }
  mpNext = (TItemListNode*)this;
  mpPrev = (TItemListNode*)this;
  mnSize = 0;
}
}  // namespace SP
// --- equivalence checker address annotations
    void operator delete(void*); // 0x00f47380
    void* operator new[](unsigned int, char*, int, unsigned int, char*, int); // 0x00f473a0

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
}
