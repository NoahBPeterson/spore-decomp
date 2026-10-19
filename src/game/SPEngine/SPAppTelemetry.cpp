// src/game/SPEngine/SPAppTelemetry.cpp -- migrated from slice(s) s007ec220, s007eb430, s007ea440 by tools/migrate/rewrite.py
// Object file: SPEngine/SPAppTelemetry.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <intrin.h>
#include "SP/cTelemetry.h"
#include "EA/DateTime/DateTime.h"
#include "SP/cTelemetryItem.h"
#include "EA/IO/MemoryStream.h"
#include <xmmintrin.h>

// ---- items of slice s007ea440 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct ObjAF {
    void* Cast(int id);
};
struct VecB { int* begin; int* end; int* cap; };
struct ObjB3 {
    int* begin; int* end; int* cap;
    void FUN_007eb000(int n, void* tag);
    ObjB3* FUN_007eb360(VecB* src);
};
struct ObjB3b { int* begin; int* end; void copyDown(int* dst, int* src); };
// ---- items of slice s007ea440 end

// ---- items of slice s007eb430 begin (TODO(rewrite): local stubs, replace by canonical classes)
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
class DateTime_s007e_b430 {
 public:
  int64_t mnSeconds;  // +0x0
  void Set(int);  // 0x0092e3d0 (EA::DateTime::DateTime::Set)
};  // namespace DateTime
}
}
namespace EA {
namespace COM {
class IRefCount_s007e_b430 {
 public:
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
};
}
}
namespace EA {
namespace COM {
class IUnknown32_s007e_b430 : public IRefCount_s007e_b430 {
 public:
  virtual void v4();
  virtual void v5();
};
}
}
namespace EA {
namespace IO {
class IStream_s007e_b430 {
 public:
  virtual void v00();     // +0x0
  virtual int AddRef();   // +0x4
  virtual int Release();  // +0x8
  virtual void v03();     // +0xc
  virtual void v04();     // +0x10
  virtual void v05();     // +0x14
  virtual void v06();     // +0x18
  virtual void v07();     // +0x1c
  virtual void v08();     // +0x20
  virtual void v09();     // +0x24
  virtual void v10();     // +0x28
  virtual void v11();     // +0x2c
};
}
}
namespace EA {
namespace IO {
class MemoryStream_s007e_b430 : public IStream_s007e_b430 {
 public:
  void* mpSharedPointer;  // +0x4
  int mnRefCount;         // +0x8
  uint32_t mnSize;        // +0xc
  uint32_t mnCapacity;    // +0x10
  uint32_t mnPosition;    // +0x14
  bool mbResizeEnabled;   // +0x18
  float mfResizeFactor;   // +0x1c
  int mnResizeIncrement;  // +0x20
};
}
}
namespace EA {
template <class T>
class RefCountTemplate_s007e_b430 {
 public:
  T mRefCount;  // +0x4
  RefCountTemplate_s007e_b430() : mRefCount(0) {}
  virtual ~RefCountTemplate_s007e_b430() {}
};
}
namespace EA {
template <class T>
class AutoRefCount_s007e_b430 {
 public:
  T* mpObject;  // +0x0
  AutoRefCount_s007e_b430(T* p = 0) : mpObject(p) {}
  ~AutoRefCount_s007e_b430() {
    if (mpObject) mpObject->Release();
  }
};
}
namespace SP {
class cISerializableObject_s007e_b430 : public EA::COM::IUnknown32_s007e_b430 {};
}
namespace SP {
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
}
namespace SP {
struct cTelemetryItem_s007e_b430 {
  EA::DateTime::DateTime_s007e_b430 mSystemTime;  // +0x0
  uint32_t mType;                      // +0x8
  TDataVec mData;                      // +0xc
};  // size 0x20
}
namespace SP {
struct TItemListNode {
  TItemListNode* mpNext;  // +0x0
  TItemListNode* mpPrev;  // +0x4
  cTelemetryItem_s007e_b430 mValue;  // +0x8
};
}
namespace SP {
struct TItemList {
  TItemListNode* mpNext;  // +0x0 sentinel next
  TItemListNode* mpPrev;  // +0x4 sentinel prev
  uint32_t mnSize;        // +0x8
  TItemList();
  TItemList(const TItemList& x);
  ~TItemList();
  TItemListNode* AllocNode(const cTelemetryItem_s007e_b430& value);
  void CopyRange(TItemListNode* first, TItemListNode* last, TItemList* dst);
};
}
namespace SP {
struct TItemMapNode {
  uint32_t mKey;         // +0x0
  TItemList mList;       // +0x4
  TItemMapNode* mpNext;  // +0x10
};  // size 0x14
}
namespace SP {
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
}
namespace SP {
struct IntVector {
  int* mpBegin;   // +0x0
  int* mpEnd;     // +0x4
  int* mpCapacity;  // +0x8
  void DoInsertValues(int* position, uint32_t n, const int& value);  // 0x007EB430
  void resize(uint32_t n);                                           // 0x007EB820
};
}
namespace SP {
class cTelemetry_s007e_b430 : public EA::RefCountTemplate_s007e_b430<int>, public cISerializableObject_s007e_b430 {
 public:
  TItemMap mStats;                          // +0xc
  int64_t mSession;                         // +0x30
  bool mbFileDump;                          // +0x38
  EA::AutoRefCount_s007e_b430<EA::IO::MemoryStream_s007e_b430> mpStream;  // +0x3c

  cTelemetry_s007e_b430();                        // 0x007EC0A0
  void FileDump();                     // 0x007EB600
  void PrepareFlush(uint32_t a, uint32_t b);  // 0x007EBBA0
  void Reset(int id);                  // 0x007EBB60
  void Flush(uint32_t id);             // 0x007EBCE0
  ~cTelemetry_s007e_b430();                       // 0x007EBE70
  bool Shutdown();                     // 0x007EBF90
  void Add(const uint32_t& key, const uint32_t& value);  // 0x007EC160
};
}
namespace SP {
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
}
namespace SP {
TDataVec::~TDataVec() {
  if (mpBegin && *(uint32_t*)((char*)mpBegin - 4)) operator delete(mpBegin);
  mpBegin = 0;
  mpEnd = 0;
  mpCapacity = 0;
}
}
namespace SP {
TItemList::TItemList() {
  mpNext = (TItemListNode*)this;
  mpPrev = (TItemListNode*)this;
  mnSize = 0;
}
}
namespace SP {
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
}
    void operator delete(void*); // 0x00f47380
    void* operator new[](unsigned int, char*, int, unsigned int, char*, int); // 0x00f473a0
// ---- items of slice s007eb430 end

// ---- items of slice s007ec220 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace IO {
void ReadInt32(void* reader, void* dst, int n, int flags);
}
}
namespace EA {
namespace IO {
void ReadTriple(void* reader, void* dst, int n, int flags);  // 0x0093A800
}
}
namespace EA {
namespace DateTime {
class DateTime_s007e_c220 {
 public:
  int64_t mnSeconds;
  void Set(int);  // 0x0092e3d0 (EA::DateTime::DateTime::Set)
};  // namespace DateTime
}
}
#define VSLOT(obj, off) (*(void***)(obj))[(off) / 4]
static void* TelemetryReader(void* iface) {
  typedef void* (__thiscall * F0)(void*);
  void* a = ((F0)VSLOT(iface, 0x20))(iface);
  return ((F0)VSLOT(a, 0x18))(a);
}
static uint32_t TelemetryVersion(void* iface) {
  typedef uint32_t(__thiscall * F0)(void*);
  return ((F0)VSLOT(iface, 0x3c))(iface);
}
static void WriteBytes(void* writer, void* p, int n) {
  typedef void(__thiscall *F0)(void*, void*, int);
  ((F0)VSLOT(writer, 0x38))(writer, p, n);
}
namespace SP {
struct cTelemetryItem_s007e_c220 {
  EA::DateTime::DateTime_s007e_c220 mSystemTime;  // +0x0
  uint32_t mType;                      // +0x8
  float* mDataBegin;                   // +0xc
  float* mDataEnd;                     // +0x10
  float* mDataCap;                     // +0x14
  const char* mDataName;               // +0x18
  uint32_t mDataFlags;                 // +0x1c
};
}
namespace SP {
struct TItemListNode_s007e_c220 {
  TItemListNode_s007e_c220* mpNext;  // +0x0
  TItemListNode_s007e_c220* mpPrev;  // +0x4
  cTelemetryItem_s007e_c220 mValue;  // +0x8
};
}
namespace SP {
struct TItemList_s007e_c220 {
  TItemListNode_s007e_c220* mpNext;  // +0x0
  TItemListNode_s007e_c220* mpPrev;  // +0x4
  uint32_t mnSize;        // +0x8
};
}
namespace SP {
struct TItemMapNode_s007e_c220 {
  uint32_t mKey;         // +0x0
  TItemList_s007e_c220 mList;       // +0x4
  TItemMapNode_s007e_c220* mpNext;  // +0x10
};
}
namespace SP {
struct TItemMap_s007e_c220 {
  uint32_t mHash;               // +0x0
  TItemMapNode_s007e_c220** mpBucketArray; // +0x4
  uint32_t mnBucketCount;       // +0x8
  uint32_t mnElementCount;      // +0xc
  float mfMaxLoadFactor;        // +0x10
  float mfGrowthFactor;         // +0x14
  uint32_t mnNextResize;        // +0x18
  uint32_t mAllocator;          // +0x1c
};
}
namespace SP {
struct cTelemetryReader {
  void* vtbl;                       // +0x0
  int32_t mRefCount;                // +0x4
  void* vtbl2;                      // +0x8
  TItemMap_s007e_c220 mStats;                  // +0xc
  int64_t mSession;                 // +0x30
  bool mbFileDump;                  // +0x38
  void* mpStream;                   // +0x3c
};
}
SP::TItemMapNode_s007e_c220* ItemMapIndex(SP::TItemMap_s007e_c220* map, const uint32_t& key);  // 0x007EBFD0
SP::TItemListNode_s007e_c220* ItemListAdd(SP::TItemList_s007e_c220* list, SP::cTelemetryItem_s007e_c220* item);  // 0x007EB720
void IntVecInsert(int* pos, uint32_t n, int* value);  // 0x007EB430
// ---- items of slice s007ec220 end

// @ 0x007eaf30
void* ObjAF::Cast(int id)
{
    if (id == 0x45a9b42)
        return (char*)this - 8;
    return 0;
}

// @ 0x007eb140
void FUN_007eb140(void* self, void* writer)
{ (void)self; (void)writer; }

// @ 0x007eb360
ObjB3* ObjB3::FUN_007eb360(VecB* src)
{
    FUN_007eb000((src->end - src->begin) >> 2, src + 1);
    int* s = src->begin;
    int* d = begin;
    while (s != src->end) {
        if (d)
            *d = *s;
        ++s; ++d;
    }
    end = d;
    return this;
}

// @ 0x007eb3b0
void ObjB3b::copyDown(int* dst, int* src)
{
    int* d = dst;
    for (int* s = src; s != end; ++s) {
        *d = *s;
        ++d;
    }
    end += ((int)src - (int)dst >> 2) * -4;
}

// @ 0x007eb600
void SP::cTelemetry::FileDump()
{
  if (!mbFileDump) return;
  extern void* GetTelemetryPath();
  extern void TelemetrySprintf(void* s, const char* fmt, ...);
  extern void FileStreamCtor(void* fs, const void* path);
  extern bool FileStreamOpen(void* fs, int, int, int, int);
  extern void FileStreamWrite(void* fs, const void* p, uint32_t n);
  extern void FileStreamClose(void* fs);
  extern void FileStreamDtor(void* fs);
  extern void RecordDoPostClose(void* fs, int, int);
  extern uint32_t StreamSize(EA::IO::MemoryStream*);
  extern void MemoryStreamLock(EA::IO::MemoryStream*);
  wchar_t path[0x120];
  path[0] = 0;
  // build path (original uses an eastl::string16 + sprintf)
  char fsbuf[0x228];
  FileStreamCtor(fsbuf, path);
  int ok = FileStreamOpen(fsbuf, 3, 4, 1, 0);
  if (ok) {
    RecordDoPostClose(fsbuf, 0, 2);
    uint32_t nSize = StreamSize(mpStream.mpObject);
    FileStreamWrite(fsbuf, &mpStream.mpObject, nSize);
    FileStreamClose(fsbuf);
  }
  FileStreamDtor(fsbuf);
}

// @ 0x007eb720
SP::TItemListNode* SP::TItemList::AllocNode(const cTelemetryItem_s007e_b430& value)
{
  TItemListNode* pNode = (TItemListNode*)EAAlloc(sizeof(TItemListNode));
  if (pNode) pNode->mValue = value;
  return pNode;
}

// @ 0x007eb7d0
void SP::TItemList::CopyRange(TItemListNode* first, TItemListNode* last, TItemList* dst)
{
  for (; first != last; first = first->mpNext) {
    TItemListNode* pNode = dst->AllocNode(first->mValue);
    pNode->mpNext = dst->mpNext;
    pNode->mpPrev = (TItemListNode*)dst;
    dst->mpNext->mpPrev = pNode;
    dst->mpNext = pNode;
    ++dst->mnSize;
  }
}

// @ 0x007eb820
void SP::IntVector::resize(uint32_t n)
{
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

// @ 0x007eb870
SP::TItemList::TItemList(const TItemList& x)
{
  mpNext = (TItemListNode*)this;
  mpPrev = (TItemListNode*)this;
  mnSize = 0;
  extern void ListCopyRange(TItemList* dst, TItemListNode* first, TItemListNode* last);
  ListCopyRange(this, x.mpNext, (TItemListNode*)&x);
}

// @ 0x007eb8d0
extern "C" SP::TItemMapNode* MakeItemMapNode(const uint32_t* pKey)
{
  SP::TItemMapNode* pNode = (SP::TItemMapNode*)EAAlloc(sizeof(SP::TItemMapNode));
  if (pNode) {
    pNode->mKey = *pKey;
    new (&pNode->mList) SP::TItemList();
  }
  pNode->mpNext = 0;
  return pNode;
}

// @ 0x007eb950
void SP::TItemMap::DoFreeNodes(TItemMapNode** bucketArray, uint32_t n)
{
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

// @ 0x007eb9e0
uint32_t SP::TItemMap::erase(const uint32_t& key)
{
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

// @ 0x007ebb60
void SP::cTelemetry_s007e_b430::Reset(int id)
{
  if (id == -1) {
    TItemMap* m = &mStats;
    m->DoFreeNodes(m->mpBucketArray, m->mnBucketCount);
    m->mnElementCount = 0;
  } else {
    mStats.erase(*(uint32_t*)&id);
  }
}

// @ 0x007ebba0
void SP::cTelemetry_s007e_b430::PrepareFlush(uint32_t stream, uint32_t id)
{
  extern void WriteUint32(uint32_t stream, const void* p, int a, int b);
  extern void WriteTime(uint32_t stream, const void* p, int a, int b);
  for (uint32_t k = 0; k <= 6; ++k) {
    if (id != 0xffffffff && k != id) continue;
    TItemMapNode** buckets = mStats.mpBucketArray;
    uint32_t nBucketCount = mStats.mnBucketCount;
    TItemMapNode* pNode = buckets[k % nBucketCount];
    while (pNode && pNode->mKey != k) pNode = pNode->mpNext;
    TItemMapNode* pFound = pNode;
    if (pFound && pFound != (TItemMapNode*)&buckets[nBucketCount * 0]) {
      // (sentinel element check omitted: matches original bounds check)
    }
    if (pFound) {
      for (TItemListNode* p = pFound->mList.mpNext; p != (TItemListNode*)&pFound->mList;
           p = p->mpNext) {
        int64_t t = p->mValue.mSystemTime.mnSeconds;
        WriteTime(stream, &t, 1, 0);
        uint32_t type = k;
        WriteUint32(stream, &type, 1, 0);
        uint32_t nCount = (uint32_t)(p->mValue.mData.mpEnd - p->mValue.mData.mpBegin) >> 2;
        WriteUint32(stream, &p->mValue.mData.mpBegin, nCount, 0);
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

// @ 0x007ebce0
void SP::cTelemetry_s007e_b430::Flush(uint32_t id)
{
  extern void* MakeTelemetryStream();
  extern void TelemetrySetFloat(int, float);
  extern void TelemetryWriteAll(void*, ...);
  if (id == 0xffffffff || id < 7) {
    EA::IO::MemoryStream_s007e_b430* pNew = 0;
    pNew = (EA::IO::MemoryStream_s007e_b430*)MakeTelemetryStream();
    EA::IO::MemoryStream_s007e_b430* pOld = mpStream.mpObject;
    if (pNew != pOld) {
      if (pNew) pNew->AddRef();
      mpStream.mpObject = pNew;
      if (pOld) pOld->Release();
    }
    TelemetrySetFloat(1, 1.0f);
    TelemetrySetFloat(2, 2.0f);
    // (write header)
    PrepareFlush((uint32_t)reinterpret_cast<size_t>(mpStream.mpObject), id);
    FileDump();
    if (mpStream.mpObject) {
      EA::IO::MemoryStream_s007e_b430* p = mpStream.mpObject;
      mpStream.mpObject = 0;
      p->Release();
    }
  }
}

// @ 0x007ebe70
SP::cTelemetry_s007e_b430::~cTelemetry_s007e_b430()
{
  mpStream.~AutoRefCount_s007e_b430<EA::IO::MemoryStream_s007e_b430>();
  mStats.DoFreeNodes(mStats.mpBucketArray, mStats.mnBucketCount);
  uint32_t nBucketCount = mStats.mnBucketCount;
  mStats.mnElementCount = 0;
  if (nBucketCount > 1) operator delete(mStats.mpBucketArray);
}

// @ 0x007ebf20
int __fastcall TelemetryRelease(int* p)
{
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

// @ 0x007ebf90
bool SP::cTelemetry_s007e_b430::Shutdown()
{
  TItemMap* m = &mStats;
  m->DoFreeNodes(m->mpBucketArray, m->mnBucketCount);
  m->mnElementCount = 0;
  EA::IO::MemoryStream_s007e_b430* p = mpStream.mpObject;
  if (p) {
    mpStream.mpObject = 0;
    p->Release();
  }
  return true;
}

// @ 0x007ec220
extern "C" int TelemetryRead(SP::cTelemetryReader* self, void* iface)
{
  uint32_t version = 0xc;
  EA::IO::ReadInt32(TelemetryReader(iface), &version, 1, 0);
  uint32_t v = TelemetryVersion(iface);
  if (v < 0x1c0012)
    version = 9;
  else {
    v = TelemetryVersion(iface);
    if (v < 0x1c0013) version = 0xf;
  }
  uint32_t key = 7;
  if (version > 6) {
    do {
      SP::TItemMapNode_s007e_c220* pNode = ItemMapIndex(&self->mStats, key);
      void* reader = TelemetryReader(iface);
      uint32_t count = 0;
      EA::IO::ReadInt32(reader, &count, 1, 0);
      uint32_t i = 0;
      if (count != 0) {
        do {
          SP::cTelemetryItem_s007e_c220 item;
          item.mSystemTime.Set(2);
          item.mDataBegin = 0;
          item.mDataEnd = 0;
          item.mDataCap = 0;
          SP::TItemListNode_s007e_c220* pNew = ItemListAdd((SP::TItemList_s007e_c220*)&pNode->mList, &item);
          pNew->mpNext = pNode->mList.mpNext;
          pNew->mpPrev = (SP::TItemListNode_s007e_c220*)&pNode->mList;
          pNode->mList.mpNext->mpPrev = pNew;
          pNode->mList.mpNext = pNew;
          ++pNode->mList.mnSize;
          if (item.mDataBegin && *(uint32_t*)((char*)item.mDataBegin - 4))
            operator delete(item.mDataBegin); // 0x00f47380
          SP::TItemListNode_s007e_c220* pItem = pNode->mList.mpNext;
          EA::IO::ReadInt32(TelemetryReader(iface), (char*)pItem + 0x10, 1, 0);
          int64_t time = 0;
          EA::IO::ReadTriple(TelemetryReader(iface), &time, 1, 0);
          uint32_t nData = 0;
          EA::IO::ReadInt32(TelemetryReader(iface), &nData, 1, 0);
          *(int64_t*)((char*)pItem + 8) = time;
          float* begin = *(float**)((char*)pItem + 0x14);
          float* end = *(float**)((char*)pItem + 0x18);
          uint32_t have = (uint32_t)(end - begin);
          if (have < nData) {
            int zero = 0;
            IntVecInsert((int*)end, nData - have, &zero);
          } else {
            *(float**)((char*)pItem + 0x18) = begin + nData;
          }
          WriteBytes(iface, begin, (int)(nData * 4));
          v = TelemetryVersion(iface);
          if (v < 0x230002 && key >= 7 && key <= 0xb) {
            float* e2 = *(float**)((char*)pItem + 0x18);
            uint32_t want = nData + 1;
            uint32_t have2 = (uint32_t)(e2 - *(float**)((char*)pItem + 0x14));
            if (have2 < want) {
              int zero = 0;
              IntVecInsert((int*)e2, want - have2, &zero);
            }
            *(float*)(*(float**)((char*)pItem + 0x14) + 0xb) = 10.0f;
          }
          ++i;
        } while (i < count);
      }
      ++key;
    } while (key <= version);
  }
  int64_t tail = 0;
  EA::IO::ReadTriple(TelemetryReader(iface), &tail, 1, 0);
  *(int64_t*)((char*)self + 0x28) = tail;
  return 1;
}
