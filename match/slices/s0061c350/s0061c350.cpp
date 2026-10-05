// Slice s0061c350: SP::Pollen transaction base constructors, request/result helpers and
// eastl vector<string> insert helpers. Flags: /O2 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "../s00622f20/s00622f20.h"

extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags,
                                          unsigned debugFlags, const char* file, int line);
extern "C" void EASTL_allocator_deallocate(void* p);

namespace SP {
namespace Pollen {
class cITransaction : public EA::RefCountVTemplate<int> {
 public:
  virtual ~cITransaction() {}
};

// fixed_vector<void*, 40> introduced at +0x30 of the transaction base
struct FixedPtrVector {
  void** mpBegin;
  void** mpEnd;
  void** mpCapacity;
  uint32_t pad[2];
  uint32_t mOverflow;
  void* mBuffer[40];
  FixedPtrVector() : mpBegin(mBuffer), mpEnd(mBuffer), mpCapacity(mBuffer + 40), mOverflow(0) {}
  FixedPtrVector& operator=(const FixedPtrVector& x);  // 0x0061c070
};
class cFeedTransactionBase : public cITransaction {
 public:
  uint32_t mpFeed;         // +0x8
  uint32_t mFeedType;      // +0xc
  uint32_t mnIntParam;     // +0x10
  uint32_t mnCount;        // +0x14
  uint32_t mUnk18;         // +0x18
  string8 mStringParam;    // +0x1c
  uint32_t pad28[1];
  FixedPtrVector mAssets;  // +0x30
  uint8_t mFlag;           // +0xe8
  cFeedTransactionBase(uint32_t type, const FixedPtrVector& assets);
  virtual ~cFeedTransactionBase();
};
class cGetAssetFeedTransaction : public cFeedTransactionBase {
 public:
  cGetAssetFeedTransaction(const FixedPtrVector& assets);
  virtual ~cGetAssetFeedTransaction();
};

// @ 0x0061c5e0
cGetAssetFeedTransaction::cGetAssetFeedTransaction(const FixedPtrVector& assets)
    : cFeedTransactionBase(4, assets) {
  mFlag = 1;
}

// ---------------------------------------------------------------------------------------------
// Remaining functions are outlined (see partial.txt).
// ---------------------------------------------------------------------------------------------
extern FixedPtrVector gTempAssets;

// @ 0x0061c570  (cFeedTransactionBase ctor)
__declspec(noinline) cFeedTransactionBase::cFeedTransactionBase(uint32_t type,
                                                               const FixedPtrVector& assets)
    : mpFeed(0),
      mFeedType(type),
      mnIntParam(0),
      mnCount(0xffffffff),
      mUnk18(0),
      mStringParam(),
      mAssets() {
  mAssets = assets;
  mFlag = 0;
}

// @ 0x0061c350
bool PollenHelper500(void* self, void* a);
bool PollenHelper500(void* self, void* a) {
  (void)self;
  (void)a;
  return false;
}

// @ 0x0061c610
void* VectorInsert70(void* self, void* a, void* b, void* c);
void* VectorInsert70(void* self, void* a, void* b, void* c) {
  (void)a;
  (void)b;
  (void)c;
  return self;
}

// @ 0x0061c760
void* VectorInsert278(void* self, void* a, void* b);
void* VectorInsert278(void* self, void* a, void* b) {
  (void)a;
  (void)b;
  return self;
}

// @ 0x0061c880
bool RequestAssetsFromFeed(void* self, void* a, void* b);
bool RequestAssetsFromFeed(void* self, void* a, void* b) {
  (void)self;
  (void)a;
  (void)b;
  return false;
}

// @ 0x0061cf60
bool GetAssetFeedHandleResult(void* self, int code, void* result, void* queue);
bool GetAssetFeedHandleResult(void* self, int code, void* result, void* queue) {
  (void)self;
  (void)code;
  (void)result;
  (void)queue;
  return false;
}

// @ 0x0061d0d0
bool EditFeedHandleResult(void* self, int code, void* result, void* queue);
bool EditFeedHandleResult(void* self, int code, void* result, void* queue) {
  (void)self;
  (void)code;
  (void)result;
  (void)queue;
  return false;
}

// @ 0x0061d1c0  (ctor, vtable 0x13fc88c)
void PollenCtor115(void* self);
void PollenCtor115(void* self) {
  (void)self;
}
}  // namespace Pollen
}  // namespace SP
