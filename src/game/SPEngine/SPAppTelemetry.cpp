// src/game/SPEngine/SPAppTelemetry.cpp -- migrated from slice(s) s01190840, s011869d0, s01183b20, s0117c560, s007ec220, s007eb430, s007ea440 by tools/migrate/rewrite.py
// Object file: SPEngine/SPAppTelemetry.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <intrin.h>
#include "SP/cTelemetry.h"
#include "EA/DateTime/DateTime.h"
#include "SP/cTelemetryItem.h"
#include "EA/IO/MemoryStream.h"
#include <xmmintrin.h>
#include "EA/ArgScript/cArguments.h"
#include "SP/cString.h"
#include "EA/CommandLine.h"
#include "EA/ArgScript/cArgumentSpec.h"
#include "EA/IO/FileStream.h"
#include "EA/IO/IStream.h"
#include <string.h>

// ---- items of slice s007ea440 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct ObjB3b {
  int* begin;
  int* end;
  int* cap;
  int* copyDown(int* dst, int* src);
  void DoInsertValues(int* position, uint32_t n, const int& value);  // 0x007EB430
};
extern "C" void operator_delete__(void* p);                                  // 0x00f47380
struct ObjAF {
    void* Cast(int id);
};
struct ObjB0 { int FUN_007eb090(); };
struct HashTable {
    char pad0[4];
    int* mpBucketArray;   // +4
    int  mnBucketCount;   // +8
    void find(void* out, const void* key);   // 0x00db4780; out is an 8-byte {node, bucket} iterator
};
struct ObjB1 {
    char pad[0xc];
    HashTable ht;         // +0xc
    int FUN_007eb100(int key);
};
struct VecB { int* begin; int* end; int* cap; };
struct ObjB3 {
    int* begin; int* end; int* cap;
    void FUN_007eb000(int n, void* tag);
    ObjB3* FUN_007eb360(VecB* src);
};
struct ObjB3b_s007e_a440 {
    int* begin;
    int* end;
    int* copyDown(int* dst, int* src);  // 0x007eb3b0 (ObjB3b::copyDown)
};
struct ObjB3f { int* first; void freeNodes(); };
bool FUN_0093aa70(void* stream, const void* p, int n, int flags);   // EA::IO::WriteUint32
bool FUN_0093ab10(void* stream, const void* p, int n, int flags);   // EA::IO::WriteUint64
struct TDataVec_s007e_a440 {
    float* mpBegin;       // +0x0
    float* mpEnd;         // +0x4
    float* mpCapacity;    // +0x8
    void*  mpName;        // +0xc
    uint32_t mFlags;      // +0x10
};
struct TItemValue {
    int64_t  mSystemTime;  // +0x0
    uint32_t mType;        // +0x8
    TDataVec_s007e_a440 mData;        // +0xc
};
struct TItemListNode_s007e_a440 {
    TItemListNode_s007e_a440* mpNext;   // +0x0
    TItemListNode_s007e_a440* mpPrev;   // +0x4
    TItemValue     mValue;   // +0x8
};
struct TItemList_s007e_a440 {
    TItemListNode_s007e_a440* mpNext;   // +0x0  sentinel
    TItemListNode_s007e_a440* mpPrev;   // +0x4
    uint32_t mnSize;         // +0x8
};
struct TItemMapNode_s007e_a440 {
    uint32_t mKey;           // +0x0
    TItemList_s007e_a440 mList;         // +0x4
    TItemMapNode_s007e_a440* mpNext;    // +0x10
};
struct TItemMap_s007e_a440 {
    uint32_t mHash;               // +0x0
    TItemMapNode_s007e_a440** mpBucketArray; // +0x4
    uint32_t mnBucketCount;       // +0x8
    uint32_t mnElementCount;      // +0xc
    float mfMaxLoadFactor;        // +0x10
    float mfGrowthFactor;         // +0x14
    uint32_t mnNextResize;        // +0x18
    uint32_t mAllocator;          // +0x1c
    struct Iterator {
        TItemMapNode_s007e_a440* mpNode;     // +0x0
        TItemMapNode_s007e_a440** mpBucket;  // +0x4
    };
    Iterator find(uint32_t key) {
        uint32_t n = key % mnBucketCount;
        for (TItemMapNode_s007e_a440* p = mpBucketArray[n]; p != 0; p = p->mpNext) {
            if (p->mKey == key) {
                Iterator it = { p, mpBucketArray + n };
                return it;
            }
        }
        Iterator it = { mpBucketArray[mnBucketCount], mpBucketArray + mnBucketCount };
        return it;
    }
};
struct CTelemetryObj {
    void* mpVtbl;        // +0x0
    TItemMap_s007e_a440 mStats;     // +0x4
    int      mPad24;     // +0x24
    int64_t  mSession;   // +0x28
    bool Write(void* writer);
};
struct IWriterObj {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
    virtual void* v6();                       // +0x18
};
struct IWriter {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
virtual void v5();
virtual void v6();
virtual void v7();
    virtual IWriterObj* v8();                 // +0x20
virtual void v9();
virtual void v10();
virtual void v11();
virtual void v12();
    virtual bool v13(const void* p, int n);   // +0x34
};
// ---- items of slice s007ea440 end

// ---- items of slice s007eb430 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern const wchar_t DAT_0141428c[];                // 0x0141428c  L"telemetry.dat"
extern const wchar_t DAT_014142a8[];                // 0x014142a8  session format
extern void* const g_vtbl_013eb90c;                 // 0x013eb90c
extern void* const g_vtbl_013eb844;                 // 0x013eb844
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
  void Set(int kind);  // 0x0092e3d0
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
  virtual uint32_t v07(); // +0x1c  byte count
  virtual void v08();     // +0x20
  virtual void v09();     // +0x24
  virtual void v10(int a, int b);  // +0x28
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
  void Init(const char* name);       // 0x0093bd50
  void SetOption(int opt, float v);  // 0x0093bb40
  void* GetData() const;             // 0x0093ba70
};
}
}
namespace EA {
namespace IO {
class FileStream_s007e_b430 {
 public:
  FileStream_s007e_b430(const wchar_t* path);                  // 0x00931e10
  ~FileStream_s007e_b430();                                    // 0x00931e70
  bool Open(uint32_t a, int b, uint32_t c, int d);  // 0x009318f0
  bool SetPosition(int a, int b);                   // 0x00931c70
  bool Write(const void* p, uint32_t n);            // 0x00931d30
  bool Close();                                     // 0x00931a70
 private:
  char mStorage[0x22c];  // EA::IO::FileStream object body
};
}
}
namespace EA {
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
}
}
namespace EA {
namespace Messaging {
IServer* GetServer();  // 0x00883860
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
class cTelemetryItem_s007e_b430 { public:
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
  __declspec(noinline) TItemListNode* AllocNode(const cTelemetryItem_s007e_b430& value);
  void CopyRange(TItemListNode* dst, TItemListNode* first, TItemList* last, uint32_t flags);
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
struct TItemMapFindResult {
  TItemMapNode* mpNode;    // +0x0
  TItemMapNode** mppSlot;  // +0x4
};
}
namespace SP {
struct TItemMapInsertResult {
  TItemMapNode* mpNode;    // +0x0
  TItemMapNode** mppSlot;  // +0x4
  bool mbInserted;         // +0x8
};
}
namespace SP {
struct TItemMapInsertPair {
  uint32_t mKey;    // +0x0
  TItemList mList;  // +0x4
};
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
  void find(TItemMapFindResult* out, const uint32_t* key);                // 0x00DB4780
  void insert(TItemMapInsertResult* out, const uint32_t* key, const void* value);  // 0x007EBAA0
  TItemList* operator[](const uint32_t& key);
};  // size 0x20
}
namespace SP {
extern TItemMapNode* gEmptyBucketArray;  // 0x0154DF28
}
namespace SP {
struct IntVecBase {
  int* mpBegin;     // +0x0
  int* mpEnd;       // +0x4
  int* mpCapacity;  // +0x8
  void DoInsertValues(int* position, uint32_t n, const int& value);  // 0x007EB430
  void copyDown(int* dst, int* src);                                 // 0x007EB3B0
};
}
namespace SP {
struct IntVector {
  int64_t mSystemTime;  // +0x0
  uint32_t mType;       // +0x8
  IntVecBase mData;     // +0xc
  void resize(uint32_t n);  // 0x007EB820
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
  __declspec(noinline) void Flush(uint32_t id);          // 0x007EBCE0
  ~cTelemetry_s007e_b430();                       // 0x007EBE70
  bool Shutdown();                     // 0x007EBF90
  void Add(const uint32_t& key, const uint32_t& value);  // 0x007EC160
};
}
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
struct ObjB0_s007e_b430 {                // cTelemetry as a hashtable holder
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

// ---- items of slice s0117c560 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct ssl_st_s0117_c560;
struct ssl_ctx_st_s0117_c560;
struct ssl_method_st_s0117_c560;
struct X509_NAME_ENTRY;
struct ASN1_OBJECT;
struct ASN1_STRING;
struct ssl_method_st_s0117_c560
{
	void* v00;                                        // 0x000
	int (*ssl_new)(ssl_st_s0117_c560*);                          // 0x004
	void* v08;                                        // 0x008
	void* v0c;                                        // 0x00c
	void* func_10;                                    // 0x010
	void* v14[4];                                     // 0x014
	int (*ssl_accept)(ssl_st_s0117_c560*);                       // 0x024
	void* v28[6];                                     // 0x028
	long (*ctrl)(ssl_st_s0117_c560*, int, long, void*);          // 0x040
	void* v44[7];                                     // 0x044
	int (*get_timeout)(void);                         // 0x060
};
struct ssl_ctx_st_s0117_c560
{
	ssl_method_st_s0117_c560* method;                            // 0x000
	void* cipher_list;                                // 0x004
	void* cipher_list_by_id;                          // 0x008
	void* cert_store;                                 // 0x00c
	void* sessions;                                   // 0x010
	int session_cache_size;                           // 0x014
	void* session_cache_head;                         // 0x018
	void* session_cache_tail;                         // 0x01c
	int session_cache_mode;                           // 0x020
	int session_timeout;                              // 0x024
	void* new_session_cb;                             // 0x028
	void* remove_session_cb;                          // 0x02c
	void* get_session_cb;                             // 0x030
	char pad34[0x2c];                                 // 0x034
	int references;                                   // 0x060
	int pad64;                                        // 0x064
	int pad68;                                        // 0x068
	int pad6c[5];                                     // 0x06c
	void* ex_data;                                    // 0x080
	int ex_data_dummy;                                // 0x084
	void* md5;                                        // 0x088
	void* sha1;                                       // 0x08c
	void* sha256;                                     // 0x090
	int z94;                                          // 0x094
	int z98;                                          // 0x098
	int z9c;                                          // 0x09c
	int za0;                                          // 0x0a0
	int a4;                                           // 0x0a4
	int a8;                                           // 0x0a8
	int ac;                                           // 0x0ac
	void* cache;                                      // 0x0b0
	int b4, b8, bc, c0, c4;                           // 0x0b4
	int c8, cc, d0, d4, d8, dc, e0, e4, e8, ec;       // 0x0c8
	void* verify_param;                               // 0x0f0
	int f4;                                           // 0x0f4
};
struct ssl_st_s0117_c560
{
	int version;                                      // 0x000
	int type;                                         // 0x004
	ssl_method_st_s0117_c560* method;                            // 0x008
	void* rbio;                                       // 0x00c
	void* wbio;                                       // 0x010
	int in_handshake;                                 // 0x014
	int rwstate;                                      // 0x018
	int pad1c;                                        // 0x01c
	void* handshake_func;                             // 0x020
	int server;                                       // 0x024
	void* new_session;                                // 0x028
	int quiet_shutdown;                               // 0x02c
	int flags30;                                      // 0x030
	int state;                                        // 0x034
	int rstate;                                       // 0x038
	void* init_buf;                                   // 0x03c
	int pad40[6];                                     // 0x040
	void* s3;                                         // 0x058
	void* p5c;                                        // 0x05c
	int f60;                                          // 0x060
	int f64;                                          // 0x064
	int f68;                                          // 0x068
	int pad6c;                                        // 0x06c
	void* verify_param;                               // 0x070
	int pad74[8];                                     // 0x074
	void* cert;                                       // 0x094
	unsigned int sid_ctx_length;                      // 0x098
	unsigned char sid_ctx[32];                        // 0x09c
	int fbc;                                          // 0x0bc
	int fc0;                                          // 0x0c0
	int fc4;                                          // 0x0c4
	int fc8;                                          // 0x0c8
	int padcc[3];                                     // 0x0cc
	ssl_ctx_st_s0117_c560* ctx;                                  // 0x0d8
	int pad_dc;                                       // 0x0dc
	int fe0;                                          // 0x0e0
	void* ex_data;                                    // 0x0e4
	int ex_data_dummy;                                // 0x0e8
	int pad_ec;                                       // 0x0ec
	int ff0;                                          // 0x0f0
	unsigned long options;                            // 0x0f4
	unsigned long f_f8;                               // 0x0f8
	unsigned long f_fc;                               // 0x0fc
};
struct ASN1_OBJECT { int dummy; };
struct ASN1_STRING { int length; int type; unsigned char* data; };
struct X509_NAME_ENTRY
{
	ASN1_OBJECT* object;                              // 0x000
	ASN1_STRING* value;                               // 0x004
	int set;                                          // 0x008
};
extern "C"
{
	void ERR_put_error(int lib, int func, int reason, const char* file, int line);   // 0x01180d50
	void ERR_add_error_data(int num, ...);                          // 0x01180a70
	unsigned long ERR_peek_error(void);                             // 0x01181100
	void* CRYPTO_malloc(int num, const char* file, int line);       // 0x01183410
	void CRYPTO_free(void* addr);                                   // 0x011835c0
	int CRYPTO_add_lock(int* pointer, int amount, int type, const char* file, int line); // 0x011815d0
	int CRYPTO_new_ex_data(int class_id, void* obj, void* ad);      // 0x01184260
	void OpenSSLDie(const char* file, int line, const char* msg);   // 0x01181510
	void operator_new_arr(void* dst, int val, int size);            // 0x011e073e

	int SSL_get_ex_data_X509_STORE_CTX_idx(void);                   // 0x01194840
	void SSL_CTX_free(ssl_ctx_st_s0117_c560*);                                 // 0x0117ba10
	void ssl_cert_free(void*);                                      // 0x01194b70
	void* ssl_cert_dup(void*);                                      // 0x01194940
	void* X509_VERIFY_PARAM_new(void);                              // 0x01194290
	void X509_VERIFY_PARAM_inherit(void* param, void* src);         // 0x011944b0
	void* X509_STORE_new(void);                                     // 0x01195420
	void* lh_new(unsigned long (*hash)(void*), int (*cmp)(void*, void*)); // 0x01194090
	unsigned long SSL_SESSION_hash(void*);                          // 0x0117b9d0
	int SSL_SESSION_cmp(void*, void*);                              // 0x0117ba00
	void* EVP_get_digestbyname(const char* name);                   // 0x011973b0
	void* FUN_011948f0(void);                                       // 0x011948f0
	void FUN_01193a90(void*, void**, void**, const char*);          // 0x01193a90
	void* FUN_01193d20(void);                                       // 0x01193d20
	void FUN_0117c200(void);                                        // 0x0117c200
	void FUN_0117c440(ssl_st_s0117_c560*);                                     // 0x0117c440

	int sk_num(const void* sk);                                     // 0x0117dde0
	void* sk_value(const void* sk, int i);                          // 0x0117ddf0
	int sk_insert(void* sk, void* p, int where);                    // 0x0117dc00
	typedef int (*sk_cmp_fn)(void*, void*);
	void* sk_new(sk_cmp_fn cmp);                                    // 0x0117db90

	void* FUN_01194ee0(void);                                       // 0x01194ee0
	void FUN_01194ef0(void*);                                       // 0x01194ef0
	void* FUN_01194f10(void*);                                      // 0x01194f10
	void ASN1_OBJECT_free(void*);                                   // 0x011998c0
	void* FUN_011991b0(void*);                                      // 0x011991b0
	int X509_NAME_ENTRY_set_data(X509_NAME_ENTRY*, int, const unsigned char*, int); // 0x0117d2a0
	void* OBJ_txt2obj(const char* txt, int no_name);                // 0x0117ffe0

	void* FUN_011918c0(void*);                                      // 0x011918c0
	int EVP_PKEY_cmp(void*, void*);                                 // 0x011913a0
	void EVP_PKEY_free(void*);                                      // 0x01191780

	int BIO_test_flags(void* b, int flags);                         // 0x01176fa0
	int BIO_get_retry_reason(void* b);                              // 0x011cac20

	int FUN_01199e70(const unsigned char** pp, long* plength, int* ptag, int* pclass, long omax); // 0x01199e70
	void* FUN_011974f0(void);                                       // 0x011974f0
	void FUN_01197500(void*);                                       // 0x01197500
	void ASN1_TYPE_set(void*, int, void*);                          // 0x01189610
	void* FUN_01199d70(int type);                                   // 0x01199d70
	int FUN_01199cb0(void*, const unsigned char*, int);             // 0x01199cb0
	void ASN1_STRING_free(void*);                                   // 0x01199db0
	int FUN_01199930(void*, const unsigned char**, int);            // 0x01199930
	int FUN_0119acf0(void*, const unsigned char**, int);            // 0x0119acf0
	int FUN_0119a850(void*, const unsigned char**, int);            // 0x0119a850
	int FUN_0117f2a0(void*, const unsigned char**, int);            // 0x0117f2a0
	void FUN_01198850(void*);                                       // 0x01198850
	int asn1_check_eoc(const unsigned char**);                      // 0x0117e310
}
// ---- items of slice s0117c560 end

// ---- items of slice s01183b20 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int u32;
void* __cdecl CRYPTO_malloc(int num, const char* file, int line);
void* __cdecl CRYPTO_realloc(void* p, int num, const char* file, int line);
void* __cdecl CRYPTO_realloc_clean(void* p, int old, int num, const char* file, int line);
void  __cdecl FUN_011835c0(void* p);                                   // OPENSSL_free
void  __cdecl ERR_put_error(int lib, int func, int reason, const char* file, int line);
void  __cdecl CRYPTO_lock(int mode, int type, const char* file, int line);
void* __cdecl operator_new__(void* p, int c, int n);                   // memset-ish
int   __cdecl FUN_0117df20(void);                                      // sk_new_null
int   __cdecl FUN_0117dde0(void* sk);                                  // sk_num
int   __cdecl sk_push(void* sk, void* p);
void  __cdecl sk_set(void* sk, int i, void* p);
void* __cdecl sk_value(void* sk, int i);
void  __cdecl sk_free(void* sk);
char* __cdecl BUF_strlcpy(char* dst, char* src, u32 n);
// ---- items of slice s01183b20 end

// callees this slice defines outside this object (rewrite.py held_callee_protos)
u32* __cdecl FUN_01183f70(void);  // 0x01183f70 (stays in the slice: not this object's)

// ---- items of slice s011869d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int   __cdecl BN_copy(int dst, int src);                                        // 0x117ab40
extern "C" int   __cdecl BN_mod_mul(int r, int a, int b, int m, int ctx);                  // 0x11ad640
extern "C" int   __cdecl FUN_011875c0(int, int, int, int, int, int);                       // 0x11875c0
extern "C" int   __cdecl BN_POOL_get(void);                                                // 0x1187990
extern "C" int   __cdecl BN_set_word(int a, int w);                                        // 0x117ac20
static const char kBnCtxFile[] = ".\\crypto\\bn\\bn_ctx.c";
struct BnStack { int* data; int count; int cap; };
static __declspec(noinline) int BnStackPushInline(BnStack* st, int value)
{
    int count = st->count;
    int cap = st->cap;
    if (count == cap) {
        int* data = (int*)CRYPTO_malloc((cap ? ((cap * 3) >> 1) : 0x20) * 4,
                                        (const char*)0x14e4c7c, 0x152);
        if (data == 0)
            return 0;
        if (count != 0) {
            for (int i = 0; i < count; ++i)
                data[i] = st->data[i];
        }
        if (cap != 0)
            FUN_011835c0(st->data);
        st->data = data;
        st->cap = cap ? ((cap * 3) >> 1) : 0x20;
    }
    st->data[st->count++] = value;
    return 1;
}
// ---- items of slice s011869d0 end

// ---- items of slice s01190840 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
void* __cdecl CRYPTO_malloc(uint size, const char* file, int line);                      // 0x01183410
uint* __cdecl FUN_01191b20(int param_1);                                                 // 0x01191b20 (defined below)
uint* __cdecl FUN_0117b100(uint* bn);                                                    // 0x0117b100 (BN_dup-ish)
void  __cdecl BN_free(void* bn);                                                         // 0x0117a970
int   __cdecl ASN1_STRING_type(void* s);                                                 // 0x011922c0
void* __cdecl EC_GROUP_dup(void* g);                                                     // 0x011b2d20
int   __cdecl EC_KEY_set_group(void* key, void* g);                                      // 0x011922d0
void  __cdecl EC_GROUP_free(void* g);                                                    // 0x011b2a60
void  __cdecl EC_POINT_free(void* p);                                                    // EC_POINT_free
int*  __cdecl FUN_0117a9d0(void);                                                        // 0x0117a9d0 BN_new
int*  __cdecl FUN_01187a80(void);                                                        // 0x01187a80 BN_CTX_new
int*  __cdecl FUN_011b2140(int* g);                                                      // 0x011b2140 EC_POINT_new
int   __cdecl EC_GROUP_get_order(int* g, int* order, int* ctx);                          // EC_GROUP_get_order
int   __cdecl BN_rand_range(int* r, int* range);                                         // BN_rand_range
int   __cdecl EC_POINT_mul(int* g, int* r, int* n, int* q, int* m, int* ctx);            // EC_POINT_mul
void  __cdecl BN_CTX_free(void* ctx);                                                    // BN_CTX_free
uint* __cdecl FUN_011b38e0(void);                                                        // 0x011b38e0 (default DSA method)
uint* __cdecl FUN_011b4020(void);                                                        // 0x011b4020 (default engine)
int   __cdecl FUN_011836c0(uint* engine);                                                // 0x011836c0 engine_init
int   __cdecl FUN_01192300(uint* engine);                                                // 0x01192300 engine get-method
void  __cdecl FUN_01183740(void* engine);                                                // 0x01183740 engine_finish
void  __cdecl FUN_01184260(int type, void* p, void* ex);                                 // 0x01184260 CRYPTO_new_ex_data
void  __cdecl FUN_011842c0(int type, void* p, void* ex);                                 // 0x011842c0 CRYPTO_free_ex_data
extern uint* DAT_016f20f0;                                                               // 0x016f20f0 default DSA method slot
__declspec(dllimport) int __cdecl strncmp(const char*, const char*, unsigned);           // msvcr90!strncmp (IAT)
int   __cdecl OBJ_sn2nid(const char* s);                                                 // OBJ_sn2nid
int   __cdecl FUN_011973a0(const char* s);                                               // 0x011973a0 EVP_get_cipherbyname
int   __cdecl FUN_01190790(char** p, int* out);                                          // 0x01190790
int*  __cdecl EVP_PKEY_type(int nid);                                                    // 0x011914c0 (EVP_PKEY_type)
int   __cdecl OBJ_obj2nid(const void* o);                                                // 0x0117fa60 OBJ_obj2nid
int   __cdecl CRYPTO_add_lock(int* addr, int amount, int type, const char* file, int line); // 0x011815d0
int   __cdecl FUN_01191ed0(int** dst, unsigned char** p, uint len);                      // 0x01191ed0 d2i_DSAPublicKey
int   __cdecl FUN_01192cb0(int** dst, unsigned char** p, uint len);                      // 0x01192cb0 d2i_EC_PUBKEY
int*  __cdecl FUN_011b3870(int nid);                                                     // 0x011b3870 EC_GROUP_new_by_curve_name
void  __cdecl FUN_011b1e60(int* g, int flag);                                            // 0x011b1e60 EC_GROUP_set_asn1_flag
int   __cdecl FUN_011b34f0(int nid, int** pkey, unsigned char** p, uint len);            // 0x011b34f0
void  __cdecl EVP_PKEY_free(void* pkey);                                                 // 0x01191780 EVP_PKEY_free
// ---- items of slice s01190840 end

// forward declarations: helpers defined later in VA order (rewrite.py forward_protos)
uint* FUN_01191f10(void);   // defined at 0x01191f10, called earlier in the TU

// callees this slice defines outside this object (rewrite.py held_callee_protos)
uint* FUN_01191da0(void);  // 0x01191da0 (stays in the slice: not this object's)

// @ 0x007eaf30
void* ObjAF::Cast(int id)
{
    if (id == 0x45a9b42)
        return (char*)this - 8;
    return 0;
}

// @ 0x007eb060
int* FUN_007eb060(int first, int last, int* dst)
{
    if (first != last) {
        int off = first - (int)dst;
        do {
            if (dst)
                *dst = *(int*)(off + (int)dst);
            ++dst;
        } while (off + (int)dst != last);
    }
    return dst;
}

// @ 0x007eb090
int ObjB0::FUN_007eb090()
{
    int self = (int)this;
    int* bucket = *(int**)(self + 0x10);
    int node = *bucket;
    int count = 0;
    if (node == 0) {
        ++bucket;
        node = *bucket;
        while (node == 0) {
            ++bucket;
            node = *bucket;
        }
    }
    int end = *(int*)(*(int*)(self + 0x10) + *(int*)(self + 0x14) * 4);
    while (node != end) {
        int n = 0;
        for (int* p = *(int**)(node + 4); p != (int*)(node + 4); p = (int*)*p)
            ++n;
        count += n;
        node = *(int*)(node + 0x10);
        while (node == 0) {
            ++bucket;
            node = *bucket;
        }
    }
    return count;
}

// @ 0x007eb100
int ObjB1::FUN_007eb100(int key)
{
    int local[2];         // iterator: {node, bucket pointer}
    // retail passes the address of the stack argument, not its value
    ht.find(local, &key);
    if (local[0] != (int)ht.mpBucketArray[ht.mnBucketCount])
        return local[0] + 4;
    return 0;
}

// @ 0x007eb140
bool CTelemetryObj::Write(void* writer)
{
    IWriter* const w = (IWriter*)writer;
    int magic = 0x45a9b42;
    FUN_0093aa70(w->v8()->v6(), &magic, 1, 0);

    for (uint32_t key = 7; key <= 0xc; ++key) {
        TItemMap_s007e_a440::Iterator it = mStats.find(key);
        TItemList_s007e_a440* pList = it.mpNode == mStats.mpBucketArray[mStats.mnBucketCount]
                               ? 0
                               : (TItemList_s007e_a440*)((char*)it.mpNode + 4);
        int n = 0;
        if (pList != 0) {
            for (TItemListNode_s007e_a440* p = pList->mpNext; p != (TItemListNode_s007e_a440*)pList; p = p->mpNext)
                ++n;
        }
        FUN_0093aa70(w->v8()->v6(), &n, 1, 0);
        if (pList == 0)
            continue;
        for (TItemListNode_s007e_a440* p = pList->mpNext; p != (TItemListNode_s007e_a440*)pList; p = p->mpNext) {
            int count = (int)(p->mValue.mData.mpEnd - p->mValue.mData.mpBegin);
            FUN_0093aa70(w->v8()->v6(), &p->mValue.mType, 1, 0);
            FUN_0093ab10(w->v8()->v6(), &p->mValue.mSystemTime, 1, 0);
            FUN_0093aa70(w->v8()->v6(), &count, 1, 0);
            w->v13(p->mValue.mData.mpBegin, count << 2);
        }
    }
    int64_t session = mSession;
    FUN_0093ab10(w->v8()->v6(), &session, 1, 0);
    return true;
}

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
int* ObjB3b_s007e_a440::copyDown(int* dst, int* src)
{
    int* e = end;
    int* d = dst;
    int* s = src;   // cursor; retail computes the new end from the original src/dst
    while (s != e) {
        *d = *s;
        ++d;
        ++s;
    }
    // this->end moves to the end of the destination run (the byte span rounded down to 4)
    long moved = (long)((int)src - (int)dst) >> 2;
    end = (int*)((char*)end - moved * 4);
    return dst;
}

// @ 0x007eb3f0
void ObjB3f::freeNodes()
{
    int* node = *(int**)this;
    while (node != (int*)this) {
        int p = node[5];
        int* next = (int*)*node;
        if (p && *(int*)(p - 4))
            operator_delete__((void*)p);
        operator_delete__(node);
        node = next;
    }
}

// @ 0x007eb430
void SP::IntVecBase::DoInsertValues(int* position, uint32_t n, const int& value)
{
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

// @ 0x007eb600
void SP::cTelemetry_s007e_b430::FileDump()
{
  if (!mbFileDump) return;
  WString16 path;
  path.RangeInitialize(GetBasePath());
  WstrFormat(&path, DAT_014142a8, mSession);
  WstrFormat(&path, DAT_0141428c);
  EA::IO::FileStream_s007e_b430 fs(path.mpBegin);
  if (fs.Open(3, 4, 1, 0)) {
    fs.SetPosition(0, 2);
    uint32_t nSize = mpStream.mpObject->v07();
    fs.Write(mpStream.mpObject->GetData(), nSize);
    fs.Close();
  }
}

// @ 0x007eb720
SP::TItemListNode* SP::TItemList::AllocNode(const cTelemetryItem_s007e_b430& value)
{
  TItemListNode* pNode = (TItemListNode*)EAAlloc(sizeof(TItemListNode));
  if (pNode) pNode->mValue = value;
  return pNode;
}

// @ 0x007eb7d0
void SP::TItemList::CopyRange(TItemListNode* dst, TItemListNode* first, TItemList* last, uint32_t flags)
{
  for (; first != (TItemListNode*)last; first = first->mpNext) {
    TItemListNode* pNode = AllocNode(first->mValue);
    pNode->mpNext = dst;
    pNode->mpPrev = dst->mpPrev;
    dst->mpPrev->mpNext = pNode;
    dst->mpPrev = pNode;
  }
}

// @ 0x007eb820
void SP::IntVector::resize(uint32_t n)
{
  uint32_t cur = (uint32_t)(mData.mpEnd - mData.mpBegin);
  if (n > cur) {
    int zero = 0;
    mData.DoInsertValues(mData.mpEnd, n - cur, zero);
  } else {
    mData.copyDown(mData.mpBegin + n, mData.mpEnd);
  }
}

// @ 0x007eb870
SP::TItemList::TItemList(const TItemList& x)
{
  mpNext = (TItemListNode*)this;
  mpPrev = (TItemListNode*)this;
  mnSize = 0;
  extern void ListCopyRange(TItemList* dst, TItemListNode* first, TItemListNode* last, uint32_t flags);
  ListCopyRange(this, x.mpNext, (TItemListNode*)&x, 0);
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

// @ 0x007ebce0
void SP::cTelemetry_s007e_b430::Flush(uint32_t id)
{
  if (id == 0xffffffff || id < 7) {
    EA::IO::MemoryStream_s007e_b430* pNew =
        (EA::IO::MemoryStream_s007e_b430*)operator new[](0x24, "App", 0, 0, 0, 0);
    if (pNew) pNew->Init("App/Telemetry");
    EA::IO::MemoryStream_s007e_b430* pOld = mpStream.mpObject;
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
      EA::IO::MemoryStream_s007e_b430* p = mpStream.mpObject;
      mpStream.mpObject = 0;
      p->Release();
    }
    msg.Destruct();
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

// @ 0x007ebfd0
SP::TItemList* SP::TItemMap::operator[](const uint32_t& key)
{
  TItemMapFindResult found;
  find(&found, &key);
  if (found.mpNode != mpBucketArray[mnBucketCount]) return &found.mpNode->mList;
  TItemMapInsertPair pair;
  pair.mKey = key;
  TItemMapInsertResult res;
  insert(&res, &pair.mKey, &key);
  return &res.mpNode->mList;
}

// @ 0x007ec0a0
SP::cTelemetry_s007e_b430::cTelemetry_s007e_b430()
: mSession(0), mbFileDump(false), mpStream(0) {
  mStats.mfMaxLoadFactor = 1.0f;
  mStats.mfGrowthFactor = 2.0f;
  mStats.mnNextResize = 0;
  mStats.mpBucketArray = (TItemMapNode**)&gEmptyBucketArray;
  mStats.mnBucketCount = 1;
  mStats.mnElementCount = 0;
}

// @ 0x007ec160
void SP::cTelemetry_s007e_b430::Add(const uint32_t& key, const uint32_t& value)
{
  if (0x2800 < (uint32_t)(((ObjB0_s007e_b430*)this)->FUN_007eb090() * 0x20)) Flush(0xffffffff);
  TItemList* pList = mStats[key];
  cTelemetryItem_s007e_b430 item;
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

// @ 0x0117c8f0
int SSL_accept(ssl_st_s0117_c560* s)
{
	if (s->handshake_func == 0)
	{
		ERR_put_error(0x14, 0xe0, 0x114, 0, 0);
		return -1;
	}
	if ((s->state & 0x3000) == 0)
		return s->method->ssl_accept(s);
	return 1;
}

// @ 0x0117ca60
ssl_ctx_st_s0117_c560* SSL_CTX_new(ssl_method_st_s0117_c560* meth)
{
	ssl_ctx_st_s0117_c560* ret = 0;

	if (meth == 0)
	{
		ERR_put_error(0x14, 0xa9, 0xc4, 0, 0);
		return 0;
	}
	if (SSL_get_ex_data_X509_STORE_CTX_idx() < 0)
	{
		ERR_put_error(0x14, 0xa9, 0x10d, 0, 0);
		goto err41;
	}
	ret = (ssl_ctx_st_s0117_c560*)CRYPTO_malloc(0xf8, ".\\ssl\\ssl_lib.c", 0x56b);
	if (ret == 0)
		goto err41;
	operator_new_arr(ret, 0, 0xf8);
	ret->method = meth;
	ret->cert_store = 0;
	ret->session_cache_mode = 2;
	ret->session_cache_size = 0x5000;
	ret->session_cache_head = 0;
	ret->session_cache_tail = 0;
	ret->session_timeout = meth->get_timeout();
	ret->new_session_cb = 0;
	ret->remove_session_cb = 0;
	ret->get_session_cb = 0;
	ret->ec = 0;
	operator_new_arr(&ret->pad34, 0, 0x2c);
	ret->references = 1;
	ret->f4 = 0;
	ret->z9c = 0;
	ret->pad64 = 0;
	ret->pad68 = 0;
	ret->ac = 0x19000;
	ret->b4 = 0;
	ret->b8 = 0;
	ret->bc = 0;
	ret->c0 = 0;
	ret->c4 = 0;
	ret->e8 = 0;
	ret->cache = FUN_011948f0();
	if (ret->cache == 0)
		goto err41;
	ret->pad6c[0] = 0;
	ret->pad6c[1] = 0;
	ret->pad6c[2] = 0;
	ret->pad6c[3] = 0;
	ret->pad6c[4] = 0;
	ret->sessions = lh_new(SSL_SESSION_hash, SSL_SESSION_cmp);
	if (ret->sessions == 0)
		goto err41;
	ret->cert_store = X509_STORE_new();
	if (ret->cert_store == 0)
		goto err41;
	FUN_01193a90(ret->method, &ret->cipher_list, &ret->cipher_list_by_id,
		"AES:ALL:!aNULL:!eNULL:+RC4:@STRENGTH");
	if (ret->cipher_list == 0)
		goto erra1;
	if (sk_num(ret->cipher_list) <= 0)
		goto erra1;
	ret->verify_param = X509_VERIFY_PARAM_new();
	if (ret->verify_param == 0)
		goto err41;
	ret->md5 = EVP_get_digestbyname("ssl2-md5");
	if (ret->md5 == 0)
		goto errf1;
	ret->sha1 = EVP_get_digestbyname("ssl3-md5");
	if (ret->sha1 == 0)
		goto errf2;
	ret->sha256 = EVP_get_digestbyname("ssl3-sha1");
	if (ret->sha256 == 0)
		goto errf3;
	ret->za0 = (int)sk_new(0);
	if (ret->za0 == 0)
		goto err41;
	CRYPTO_new_ex_data(2, ret, &ret->ex_data);
	ret->z94 = 0;
	ret->z98 = (int)FUN_01193d20();
	return ret;

err41:
	ERR_put_error(0x14, 0xa9, 0x41, 0, 0);
	goto err;
erra1:
	ERR_put_error(0x14, 0xa9, 0xa1, 0, 0);
	goto err;
errf1:
	ERR_put_error(0x14, 0xa9, 0xf1, 0, 0);
	goto err;
errf2:
	ERR_put_error(0x14, 0xa9, 0xf2, 0, 0);
	goto err;
errf3:
	ERR_put_error(0x14, 0xa9, 0xf3, 0, 0);
	goto err;
err:
	if (ret != 0)
		SSL_CTX_free(ret);
	return 0;
}

// @ 0x0117df20
__declspec(noinline) void* sk_new_null(void)
{
	return sk_new(0);
}

// @ 0x01184320
int __cdecl FUN_01184320(int* param_1, int param_2, int param_3)
{
    if (*param_1 == 0) {
        int iVar1 = FUN_0117df20();
        *param_1 = iVar1;
        if (iVar1 == 0) {
            ERR_put_error(0xf, 0x66, 0x41, 0, 0);
            return 0;
        }
    }
    int iVar1 = FUN_0117dde0((void*)*param_1);
    while (1) {
        if (iVar1 > param_2) {
            sk_set((void*)*param_1, param_2, (void*)param_3);
            return 1;
        }
        int iVar2 = sk_push((void*)*param_1, 0);
        if (iVar2 == 0) break;
        iVar1 = iVar1 + 1;
    }
    ERR_put_error(0xf, 0x66, 0x41, 0, 0);
    return 0;
}

// @ 0x011843b0
int __cdecl FUN_011843b0(int param_1, int param_2, int* param_3)
{
    int iVar6 = 0;
    int iVar2 = (int)FUN_01183f70();
    if (iVar2 == 0)
        return 0;
    *param_3 = 0;
    CRYPTO_lock(5, 2, ".\\crypto\\ex_data.c", 0x199);
    int iVar3 = FUN_0117dde0(*(void**)(iVar2 + 4));
    if (0 < iVar3) {
        iVar6 = (int)CRYPTO_malloc(iVar3 * 4, ".\\crypto\\ex_data.c", 0x19d);
        if (iVar6 != 0) {
            for (int iVar5 = 0; iVar5 < iVar3; iVar5 = iVar5 + 1) {
                int uVar4 = (int)sk_value(*(void**)(iVar2 + 4), iVar5);
                *(int*)(iVar6 + iVar5 * 4) = uVar4;
            }
        }
    }
    CRYPTO_lock(6, 2, ".\\crypto\\ex_data.c", 0x1a4);
    if ((0 < iVar3) && (iVar6 == 0)) {
        ERR_put_error(0xf, 0x6c, 0x41, 0, 0);
        return 0;
    }
    for (int iVar2b = 0; iVar2b < iVar3; iVar2b = iVar2b + 1) {
        int iVar5 = *(int*)(iVar6 + iVar2b * 4);
        if ((iVar5 != 0) && (*(int*)(iVar5 + 8) != 0)) {
            int uVar4 = 0;
            if (*param_3 != 0) {
                iVar5 = FUN_0117dde0((void*)*param_3);
                if (iVar2b < iVar5)
                    uVar4 = (int)sk_value((void*)*param_3, iVar2b);
                else
                    uVar4 = 0;
            }
            u32* puVar1 = *(u32**)(iVar6 + iVar2b * 4);
            (*(void(**)(int, int, int*, int, u32, u32))(puVar1[2]))
                (param_2, uVar4, param_3, iVar2b, puVar1[0], puVar1[1]);
        }
    }
    if (iVar6 != 0)
        FUN_011835c0((void*)iVar6);
    return 1;
}

// @ 0x011844e0
int __cdecl FUN_011844e0(int param_1, int param_2, int* param_3)
{
    int iVar6 = 0;
    if (*param_3 == 0)
        return 1;
    int iVar2 = (int)FUN_01183f70();
    if (iVar2 == 0)
        return 0;
    CRYPTO_lock(5, 2, ".\\crypto\\ex_data.c", 0x1c5);
    int iVar3 = FUN_0117dde0(*(void**)(iVar2 + 4));
    int iVar4 = FUN_0117dde0((void*)*param_3);
    if (iVar4 < iVar3)
        iVar3 = iVar4;
    if (0 < iVar3) {
        iVar6 = (int)CRYPTO_malloc(iVar3 * 4, ".\\crypto\\ex_data.c", 0x1cc);
        if (iVar6 != 0) {
            for (iVar4 = 0; iVar4 < iVar3; iVar4 = iVar4 + 1) {
                int uVar5 = (int)sk_value(*(void**)(iVar2 + 4), iVar4);
                *(int*)(iVar6 + iVar4 * 4) = uVar5;
            }
        }
    }
    CRYPTO_lock(6, 2, ".\\crypto\\ex_data.c", 0x1d3);
    if ((0 < iVar3) && (iVar6 == 0)) {
        ERR_put_error(0xf, 0x6a, 0x41, 0, 0);
        return 0;
    }
    for (int iVar2b = 0; iVar2b < iVar3; iVar2b = iVar2b + 1) {
        int uVar5 = 0;
        if (*param_3 != 0) {
            iVar4 = FUN_0117dde0((void*)*param_3);
            if (iVar2b < iVar4)
                uVar5 = (int)sk_value((void*)*param_3, iVar2b);
            else
                uVar5 = 0;
        }
        u32* puVar1 = *(u32**)(iVar6 + iVar2b * 4);
        int uStack_4 = uVar5;
        if ((puVar1 != 0) && (puVar1[4] != 0)) {
            (*(void(**)(int, int*, int*, int, u32, u32))(puVar1[4]))
                (param_2, param_3, &uStack_4, iVar2b, puVar1[0], puVar1[1]);
        }
        FUN_01184320((int*)param_2, iVar2b, uStack_4);
    }
    if (iVar6 != 0)
        FUN_011835c0((void*)iVar6);
    return 1;
}

// @ 0x01184640
void __cdecl FUN_01184640(int param_1, int param_2, int* param_3)
{
    int iVar6 = 0;
    int iVar2 = (int)FUN_01183f70();
    if (iVar2 != 0) {
        CRYPTO_lock(5, 2, ".\\crypto\\ex_data.c", 0x1f0);
        int iVar3 = FUN_0117dde0(*(void**)(iVar2 + 4));
        if (0 < iVar3) {
            iVar6 = (int)CRYPTO_malloc(iVar3 * 4, ".\\crypto\\ex_data.c", 500);
            if (iVar6 != 0) {
                for (int iVar5 = 0; iVar5 < iVar3; iVar5 = iVar5 + 1) {
                    int uVar4 = (int)sk_value(*(void**)(iVar2 + 4), iVar5);
                    *(int*)(iVar6 + iVar5 * 4) = uVar4;
                }
            }
        }
        CRYPTO_lock(6, 2, ".\\crypto\\ex_data.c", 0x1fb);
        if ((0 < iVar3) && (iVar6 == 0)) {
            ERR_put_error(0xf, 0x6b, 0x41, 0, 0);
            return;
        }
        for (int iVar2b = 0; iVar2b < iVar3; iVar2b = iVar2b + 1) {
            int iVar5 = *(int*)(iVar6 + iVar2b * 4);
            if ((iVar5 != 0) && (*(int*)(iVar5 + 0xc) != 0)) {
                int uVar4 = 0;
                if (*param_3 != 0) {
                    iVar5 = FUN_0117dde0((void*)*param_3);
                    if (iVar2b < iVar5)
                        uVar4 = (int)sk_value((void*)*param_3, iVar2b);
                    else
                        uVar4 = 0;
                }
                u32* puVar1 = *(u32**)(iVar6 + iVar2b * 4);
                (*(void(**)(int, int, int*, int, u32, u32))(puVar1[3]))
                    (param_2, uVar4, param_3, iVar2b, puVar1[0], puVar1[1]);
            }
        }
        if (iVar6 != 0)
            FUN_011835c0((void*)iVar6);
        if (*param_3 != 0) {
            sk_free((void*)*param_3);
            *param_3 = 0;
        }
    }
}

// @ 0x01184770
u32* __cdecl FUN_01184770(void)
{
    u32* puVar1 = (u32*)CRYPTO_malloc(0xc, ".\\crypto\\buffer\\buffer.c", 0x43);
    if (puVar1 == 0) {
        ERR_put_error(7, 0x65, 0x41, 0, 0);
        return 0;
    }
    *puVar1 = 0;
    puVar1[2] = 0;
    puVar1[1] = 0;
    return puVar1;
}

// @ 0x011847f0
int __cdecl FUN_011847f0(int* param_1, int param_2)
{
    int iVar1 = *param_1;
    if (iVar1 < param_2) {
        if (param_1[2] < param_2) {
            iVar1 = ((param_2 + 3) / 3) * 4;
            int iVar2;
            if (param_1[1] == 0)
                iVar2 = (int)CRYPTO_malloc(iVar1, ".\\crypto\\buffer\\buffer.c", 0x6e);
            else
                iVar2 = (int)CRYPTO_realloc((void*)param_1[1], iVar1, ".\\crypto\\buffer\\buffer.c", 0x70);
            if (iVar2 == 0) {
                ERR_put_error(7, 100, 0x41, 0, 0);
                return 0;
            }
            param_1[1] = iVar2;
            param_1[2] = iVar1;
            operator_new__((void*)(*param_1 + iVar2), 0, param_2 - *param_1);
            *param_1 = param_2;
            return param_2;
        }
        operator_new__((void*)(param_1[1] + iVar1), 0, param_2 - iVar1);
    }
    *param_1 = param_2;
    return param_2;
}

// @ 0x011848a0
int __cdecl FUN_011848a0(int* param_1, int param_2)
{
    int iVar1 = *param_1;
    if (iVar1 >= param_2) {
        operator_new__((void*)(param_1[1] + param_2), 0, iVar1 - param_2);
        *param_1 = param_2;
        return param_2;
    }
    if (param_1[2] >= param_2) {
        operator_new__((void*)(param_1[1] + iVar1), 0, param_2 - iVar1);
        *param_1 = param_2;
        return param_2;
    }
    iVar1 = ((param_2 + 3) / 3) * 4;
    int iVar2;
    if (param_1[1] == 0)
        iVar2 = (int)CRYPTO_malloc(iVar1, ".\\crypto\\buffer\\buffer.c", 0x93);
    else
        iVar2 = (int)CRYPTO_realloc_clean((void*)param_1[1], param_1[2], iVar1,
                                          ".\\crypto\\buffer\\buffer.c", 0x95);
    if (iVar2 == 0) {
        ERR_put_error(7, 0x69, 0x41, 0, 0);
        return 0;
    }
    param_1[1] = iVar2;
    param_1[2] = iVar1;
    operator_new__((void*)(*param_1 + iVar2), 0, param_2 - *param_1);
    *param_1 = param_2;
    return param_2;
}

// @ 0x01184a20
int __cdecl FUN_01184a20(int param_1, int param_2)
{
    if (param_1 == 0)
        return 0;
    int iVar1 = (int)CRYPTO_malloc(param_2 + 1, ".\\crypto\\buffer\\buffer.c", 0xb1);
    if (iVar1 == 0) {
        ERR_put_error(7, 0x68, 0x41, 0, 0);
        return 0;
    }
    BUF_strlcpy((char*)iVar1, (char*)param_1, param_2 + 1);
    return iVar1;
}

// @ 0x011869d0
void lib_cblock_FUN_011869d0(void)
{}

// @ 0x01186d30
void lib_cblock_FUN_01186d30(void)
{}

// @ 0x01187540
int lib_cblock_BN_mod_mul_wrap(int param_1, int param_2, int* param_3, int param_4)
{
    int r = 1;
    if (*param_3 != 0 && param_3[1] != 0) {
        if (param_2 != 0) {
            if (BN_copy(param_2, param_3[1]) == 0) {
                r = 0;
            }
        }
        if (BN_mod_mul(param_1, param_1, *param_3, param_3[3], param_4) == 0) {
            r = 0;
        }
        return r;
    }
    ERR_put_error(3, 0x64, 0x6b, 0, 0);
    return 0;
}

// @ 0x011875c0
void lib_cblock_FUN_011875c0(void)
{}

// @ 0x011877a0
int lib_cblock_BN_mod_mul_wrap2(int* param_1, int param_2)
{
    int v = *param_1;
    int r = 0;
    if (v == 0 || param_1[1] == 0) {
        ERR_put_error(3, 0x67, 0x6b, 0, 0);
        goto END;
    }
    param_1[5] = param_1[5] - 1;
    if ((param_1[5] == 0) && (param_1[2] != 0) && ((*(char*)((char*)param_1 + 0x18) & 2) == 0)) {
        v = FUN_011875c0((int)param_1, 0, 0, param_2, 0, 0);
        if (v == 0) {
            goto END;
        }
    } else if ((*(char*)((char*)param_1 + 0x18) & 1) == 0) {
        v = BN_mod_mul(v, v, v, param_1[3], param_2);
        if (v == 0) {
            goto END;
        }
        v = param_1[1];
        v = BN_mod_mul(v, v, v, param_1[3], param_2);
        if (v == 0) {
            goto END;
        }
    }
    r = 1;
END:
    if (param_1[5] == 0) {
        param_1[5] = 0x20;
    }
    return r;
}

// @ 0x01187840
int lib_cblock_BN_mod_mul_wrap3(int param_1, int param_2, int* param_3, int param_4)
{
    if (*param_3 != 0 && param_3[1] != 0) {
        int v = param_3[1];
        if (param_2 != 0) {
            v = param_2;
        }
        v = BN_mod_mul(param_1, param_1, v, param_3[3], param_4);
        if (v >= 0) {
            if (lib_cblock_BN_mod_mul_wrap2(param_3, param_4) == 0) {
                return 0;
            }
        }
        return v;
    }
    ERR_put_error(3, 0x65, 0x6b, 0, 0);
    return 0;
}

// @ 0x01187a80
int* lib_cblock_BN_CTX_new(void)
{
    int* p = (int*)CRYPTO_malloc(0x2c, kBnCtxFile, 0xd8);
    if (p == 0) {
        ERR_put_error(3, 0x6a, 0x41, 0, 0);
        return 0;
    }
    p[2] = 0;
    p[1] = 0;
    p[0] = 0;
    p[4] = 0;
    p[3] = 0;
    p[5] = 0;
    p[7] = 0;
    p[6] = 0;
    p[8] = 0;
    p[9] = 0;
    p[10] = 0;
    return p;
}

// @ 0x01187b00
void lib_cblock_BN_STACK_push(int param_1)
{
    if (*(int*)(param_1 + 0x24) == 0 && *(int*)(param_1 + 0x28) == 0) {
        if (BnStackPushInline((BnStack*)((char*)param_1 + 0x14), *(int*)(param_1 + 0x20)) == 0) {
            ERR_put_error(3, 0x81, 0x6d, 0, 0);
            ++*(int*)(param_1 + 0x24);
        }
    } else {
        ++*(int*)(param_1 + 0x24);
    }
}

// @ 0x01187b90
int lib_cblock_BN_POOL_get(int param_1)
{
    if (*(int*)(param_1 + 0x24) == 0 && *(int*)(param_1 + 0x28) == 0) {
        int r = BN_POOL_get();
        if (r == 0) {
            *(int*)(param_1 + 0x28) = 1;
            ERR_put_error(3, 0x74, 0x6d, 0, 0);
            return 0;
        }
        BN_set_word(r, 0);
        ++*(int*)(param_1 + 0x20);
        return r;
    }
    return 0;
}

// @ 0x01187be0
void lib_cblock_FUN_01187be0(void)
{}

// @ 0x01190db0
bool FUN_01190db0(char* param_1, int* param_2)
{
    *param_2 = 0;
    char* p = param_1;
    if (p == 0 || *p == '\0' || *p == '\n') return true;
    if (strncmp(p, "Proc-Type: ", 0xb) == 0) {
        if (p[0xb] == '4' && p[0xc] == ',') {
            p += 0xd;
            if (strncmp(p, "ENCRYPTED", 9) != 0) {
                ERR_put_error(9, 0x6b, 0x6a, 0, 0);
                return false;
            }
            char c = *p;
            while (c != '\n') {
                if (c == '\0') goto err_70;
                p += 1;
                c = *p;
            }
            if (*p != '\0') {
                if (strncmp(p + 1, "DEK-Info: ", 10) != 0) {
                    ERR_put_error(9, 0x6b, 0x69, 0, 0);
                    return false;
                }
                p += 0xb;
                char* q = p;
                while ((c = *q, c > '@' && c < '[') ||
                       (c == '-' || (unsigned char)(c - 0x30) < 10)) {
                    q += 1;
                }
                *q = '\0';
                OBJ_sn2nid(p);
                int nid = FUN_011973a0(p);
                *param_2 = nid;
                *q = c;
                p = q + 1;
                if (nid == 0) {
                    ERR_put_error(9, 0x6b, 0x72, 0, 0);
                    return false;
                }
                return FUN_01190790(&p, param_2 + 1) != 0;
            }
err_70:
            ERR_put_error(9, 0x6b, 0x70, 0, 0);
            return false;
        }
    } else {
        ERR_put_error(9, 0x6b, 0x6b, 0, 0);
    }
    return false;
}

// @ 0x01191470
uint* FUN_01191470(void)
{
    uint* p = (uint*)CRYPTO_malloc(0x18, ".\\crypto\\evp\\p_lib.c", 0x13d);
    if (!p) {
        ERR_put_error(6, 0x6a, 0x41, 0, 0);
        return 0;
    }
    p[0] = 0;
    p[2] = 1;
    p[3] = 0;
    p[5] = 0;
    p[4] = 1;
    return p;
}

// @ 0x01191620
int FUN_01191620(int* param_1, int* param_2)
{
    int v, old;
    int kind = *param_2;
    if (*param_1 != kind) {
        ERR_put_error(6, 0x67, 0x65, 0, 0);
        return 0;
    }
    if (kind == 0x74) {
        if (((int*)param_2[3])[3] == 0 || ((int*)param_2[3])[4] == 0 ||
            ((int*)param_2[3])[5] == 0) {
            ERR_put_error(6, 0x67, 0x67, 0, 0);
            return 0;
        }
    }
    if (kind == 0x198) {
        if (ASN1_STRING_type((void*)param_2[3]) == 0) {
            ERR_put_error(6, 0x67, 0x67, 0, 0);
            return 0;
        }
    }
    if (*param_1 == 0x74) {
        v = (int)FUN_0117b100((uint*)((int*)param_2[3])[3]);
        if (!v) return 0;
        old = ((int*)param_1[3])[3];
        if (old) BN_free((void*)old);
        ((int*)param_1[3])[3] = v;
        v = (int)FUN_0117b100((uint*)((int*)param_2[3])[4]);
        if (!v) return 0;
        old = ((int*)param_1[3])[4];
        if (old) BN_free((void*)old);
        ((int*)param_1[3])[4] = v;
        v = (int)FUN_0117b100((uint*)((int*)param_2[3])[5]);
        if (!v) return 0;
        old = ((int*)param_1[3])[5];
        if (old) BN_free((void*)old);
        ((int*)param_1[3])[5] = v;
    }
    if (*param_1 == 0x198) {
        void* g = EC_GROUP_dup((void*)ASN1_STRING_type((void*)param_2[3]));
        if (!g) return 0;
        if (!EC_KEY_set_group((void*)param_1[3], g)) return 0;
        EC_GROUP_free(g);
    }
    return 1;
}

// @ 0x011918c0
int* FUN_011918c0(int* param_1)
{
    int* ret = 0;
    unsigned char* p;
    if (param_1 == 0) return 0;
    if (param_1[2] != 0) {
        CRYPTO_add_lock((int*)(param_1[2] + 8), 1, 10, ".\\crypto\\asn1\\x_pubkey.c", 0x111);
        return (int*)param_1[2];
    }
    if (param_1[1] == 0) return 0;
    int nid = OBJ_obj2nid((void*)*param_1);
    ret = (int*)FUN_01191470();
    if (ret == 0) goto err_41;
    *ret = (int)EVP_PKEY_type(nid);
    {
        int* param = (int*)((int*)*param_1)[1];
        if (*ret == 0x74) {
            if (param != 0 && *param == 0x10) {
                ret[3] = (int)FUN_01191da0();
                if (ret[3] == 0) goto err_41;
                *(int*)(ret[3] + 8) = 0;
                p = (unsigned char*)((int*)param[1])[2];
                if (!FUN_01191ed0((int**)(ret + 3), &p, (uint)((int*)param[1])[0]))
                    goto cleanup;
            }
            ret[4] = 1;
            goto lab_aa0;
        }
        if (*ret != 0x198) goto lab_aa0;
        if (param != 0 && *param == 0x10) {
            ret[3] = (int)FUN_01191f10();
            if (ret[3] == 0) goto err_41;
            p = (unsigned char*)((int*)param[1])[2];
            if (!FUN_01192cb0((int**)(ret + 3), &p, (uint)((int*)param[1])[0])) {
                ERR_put_error(0xb, 0x77, 0x10, 0, 0);
                goto cleanup;
            }
            goto lab_a95;
        }
        if (param != 0 && *param == 6) {
            if (ret[3] == 0) ret[3] = (int)FUN_01191f10();
            int ec = ret[3];
            if (ec == 0) goto cleanup;
            int* g = FUN_011b3870(OBJ_obj2nid((void*)param[1]));
            if (g == 0) goto cleanup;
            FUN_011b1e60(g, 1);
            if (!EC_KEY_set_group((void*)ec, g)) goto cleanup;
            EC_GROUP_free(g);
        }
lab_a95:
        ret[4] = 1;
    }
lab_aa0:
    p = (unsigned char*)((int*)param_1[1])[2];
    if (!FUN_011b34f0(nid, &ret, &p, (uint)*(int*)param_1[1])) {
        ERR_put_error(0xb, 0x77, 0x66, 0, 0);
        goto cleanup;
    }
    param_1[2] = (int)ret;
    CRYPTO_add_lock((int*)((char*)ret + 8), 1, 10, ".\\crypto\\asn1\\x_pubkey.c", 0x173);
    return ret;
err_41:
    ERR_put_error(0xb, 0x77, 0x41, 0, 0);
cleanup:
    if (ret != 0) EVP_PKEY_free(ret);
    return 0;
}

// @ 0x01191b20
uint* FUN_01191b20(int param_1)
{
    uint* p = (uint*)CRYPTO_malloc(0x44, ".\\crypto\\dsa\\dsa_lib.c", 0x75);
    if (!p) {
        ERR_put_error(0xa, 0x67, 0x41, 0, 0);
        return 0;
    }
    uint* meth = DAT_016f20f0;
    if (!meth) {
        meth = FUN_011b38e0();
        DAT_016f20f0 = meth;
    }
    p[0xf] = (uint)meth;
    if (param_1 != 0) {
        if (!FUN_011836c0((uint*)param_1)) {
            ERR_put_error(0xa, 0x67, 0x26, 0, 0);
            FUN_011835c0(p);
            return 0;
        }
        p[0x10] = (uint)param_1;
    } else {
        p[0x10] = (uint)FUN_011b4020();
    }
    if (p[0x10] != 0) {
        uint* m = (uint*)FUN_01192300((uint*)p[0x10]);
        p[0xf] = (uint)m;
        if (!m) {
            ERR_put_error(0xa, 0x67, 0x26, 0, 0);
            FUN_01183740((void*)p[0x10]);
            FUN_011835c0(p);
            return 0;
        }
    }
    p[0] = 0;
    p[1] = 0;
    p[2] = 1;
    p[3] = 0;
    p[4] = 0;
    p[5] = 0;
    p[6] = 0;
    p[7] = 0;
    p[8] = 0;
    p[9] = 0;
    p[0xb] = 0;
    p[0xc] = 1;
    p[0xa] = *(uint*)(p[0xf] + 0x20);
    FUN_01184260(7, p, p + 0xd);
    int (*init)(void*) = (int (*)(void*))*(uint*)(p[0xf] + 0x18);
    if (init != 0) {
        if (!init(p)) {
            if (p[0x10]) FUN_01183740((void*)p[0x10]);
            FUN_011842c0(7, p, p + 0xd);
            FUN_011835c0(p);
            p = 0;
        }
    }
    return p;
}

// @ 0x01191f10
uint* FUN_01191f10(void)
{
    uint* p = (uint*)CRYPTO_malloc(0x20, ".\\crypto\\ec\\ec_key.c", 0x49);
    if (!p) {
        ERR_put_error(0x10, 0xb6, 0x41, 0, 0);
        return 0;
    }
    p[0] = 1;
    p[1] = 0;
    p[2] = 0;
    p[3] = 0;
    p[4] = 0;
    p[5] = 4;
    p[6] = 1;
    p[7] = 0;
    return p;
}

// @ 0x01192190
uint FUN_01192190(int param_1)
{
    int iv5 = 0;
    int iv4 = 0;
    uint local_4 = 0;
    if (param_1 == 0 || *(int*)(param_1 + 4) == 0) {
        ERR_put_error(0x10, 0xb3, 0x43, 0, 0);
        return 0;
    }
    int iv1 = (int)FUN_0117a9d0();
    if (iv1 != 0) {
        int iv2 = (int)FUN_01187a80();
        if (iv2 != 0) {
            iv5 = *(int*)(param_1 + 0xc);
            if (iv5 == 0) iv5 = (int)FUN_0117a9d0();
            if (iv5 != 0 &&
                EC_GROUP_get_order((int*)*(int*)(param_1 + 4), (int*)iv1, (int*)iv2)) {
                do {
                    if (!BN_rand_range((int*)iv5, (int*)iv1)) goto cleanup;
                } while (*(int*)(iv5 + 4) == 0);
                iv4 = *(int*)(param_1 + 8);
                if (iv4 == 0) iv4 = (int)FUN_011b2140((int*)*(int*)(param_1 + 4));
                if (iv4 != 0 &&
                    EC_POINT_mul((int*)*(int*)(param_1 + 4), (int*)iv4, (int*)iv5, 0, 0,
                                 (int*)iv2)) {
                    *(int*)(param_1 + 0xc) = iv5;
                    *(int*)(param_1 + 8) = iv4;
                    local_4 = 1;
                }
            }
        }
cleanup:
        BN_free((void*)iv1);
        if (iv4 != 0 && *(int*)(param_1 + 8) == 0) EC_POINT_free((void*)iv4);
        if (iv5 != 0 && *(int*)(param_1 + 0xc) == 0) BN_free((void*)iv5);
        if (iv2 != 0) BN_CTX_free((void*)iv2);
    }
    return local_4;
}
