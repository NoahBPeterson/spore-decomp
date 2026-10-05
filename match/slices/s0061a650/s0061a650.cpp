// Slice s0061a650: SP::Pollen feed/YouTube/telemetry transaction constructors and request
// builders. Flags: /O2 /MD /Gy /TP (no /EHsc).
#include "../s00622f20/s00622f20.h"

extern "C" unsigned int __cdecl strlen(const char*);
#pragma intrinsic(strlen)

namespace SP {
namespace Pollen {
class cITransaction : public EA::RefCountVTemplate<int> {
 public:
  virtual ~cITransaction() {}
};

// retail cFeedTransactionBase (0xec bytes) -- only the fields the constructors touch
struct FixedPtrVector {
  void** mpBegin;
  void** mpEnd;
  void** mpCapacity;
  uint32_t pad[2];
  uint32_t mOverflow;
  uint32_t mBuffer[40];
};
class cFeedTransactionBase : public cITransaction {
 public:
  uint32_t mpFeed;       // +0x8
  uint32_t mFeedType;    // +0xc
  uint32_t mnIntParam;   // +0x10
  uint32_t mnCount;      // +0x14
  uint32_t mUnk18;       // +0x18
  string8 mStringParam;  // +0x1c
  uint32_t pad28[1];
  FixedPtrVector mAssets;  // +0x30
  uint8_t mFlag;           // +0xe8
  cFeedTransactionBase(uint32_t type, const char* str, uint32_t intParam);
};
cFeedTransactionBase::cFeedTransactionBase(uint32_t type, const char* str, uint32_t intParam)
    : mpFeed(0), mFeedType(type), mnIntParam(intParam), mnCount(0xffffffff), mUnk18(0),
      mStringParam(), mFlag(0) {
  mStringParam.assign(str, str + strlen(str));
}

class cGetAssetFeedTransaction : public cFeedTransactionBase {
 public:
  cGetAssetFeedTransaction(uint32_t lo, uint32_t hi);
};
class cGetAssetFeedTransactionEx : public cFeedTransactionBase {
 public:
  uint64_t mId;        // +0xf0
  string8 mExtra;      // +0xf8
  cGetAssetFeedTransactionEx(uint32_t lo, uint32_t hi);
};

extern void* gEmptyBucketArray;  // 0x0154df28
struct hash_set_u64 {  // eastl::hash_set<uint64_t>, 0x20 bytes
  uint32_t mfRehash;
  void** mpBucketArray;
  uint32_t mnBucketCount;
  uint32_t mnElementCount;
  float mLoadFactor;
  float mGrowFactor;
  uint32_t pad0;
  uint32_t pad1;
  hash_set_u64() {
    mLoadFactor = 1.0f;
    mGrowFactor = 2.0f;
    mnBucketCount = 1;
    mnElementCount = 0;
    pad0 = 0;
    mpBucketArray = &gEmptyBucketArray;
  }
};
class cEditFeedTransaction : public cITransaction {
 public:
  uint32_t mpFeed;         // +0x8
  int mOpType;             // +0xc
  string8 mFeedURI;        // +0x10
  string8 mFeedDescription;  // +0x20
  hash_set_u64 mAssetsToAdd;     // +0x30
  hash_set_u64 mAssetsToRemove;  // +0x50
  cEditFeedTransaction(int opType);
};

// @ 0x0061a810
cGetAssetFeedTransaction::cGetAssetFeedTransaction(uint32_t lo, uint32_t hi)
    : cFeedTransactionBase(3, (const char*)0x013ec47c, 0) {
  string8 tmp(eastl::basic_string<char>::CtorSprintf(), "%I64u", lo, hi);
  mStringParam.assign(tmp.mpBegin, tmp.mpEnd);
  mFlag = 1;
}

// @ 0x0061a8b0
cGetAssetFeedTransactionEx::cGetAssetFeedTransactionEx(uint32_t lo, uint32_t hi)
    : cFeedTransactionBase(3, (const char*)0x013ec47c, 0), mId((uint64_t)lo | ((uint64_t)hi << 32)) {
  mExtra.mpBegin = 0;
  mExtra.mpEnd = 0;
  mExtra.mpCapacity = 0;
  string8 tmp(eastl::basic_string<char>::CtorSprintf(), "%I64u", lo, hi);
  mStringParam.assign(tmp.mpBegin, tmp.mpEnd);
  mFlag = 1;
}

// @ 0x0061a970
cEditFeedTransaction::cEditFeedTransaction(int opType)
    : mpFeed(0), mOpType(opType), mFeedURI(), mFeedDescription(), mAssetsToAdd(), mAssetsToRemove() {}

// ---------------------------------------------------------------------------------------------
// Request builders. These post HTTP requests through the shared EA::Internet plumbing; the
// full bodies are not reproduced (see partial.txt / nonmatching.txt).
// ---------------------------------------------------------------------------------------------
extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags,
                                          unsigned debugFlags, const char* file, int line);
extern "C" void EASTL_allocator_deallocate(void* p);
bool CreateHTTPGetRequest(const char* url, void* body, void** out);  // 0x00944450

class cUserMatchTransaction : public cITransaction {
 public:
  uint32_t mpFeed;    // +0x8
  uint64_t mAssetID;  // +0x10
  uint32_t mnCount;   // +0x18
  bool ConstructRequest(void** ppRequest);
};
class cHandshakeTransaction : public cITransaction {
 public:
  uint32_t pad0[2];
  uint32_t pad1[4];
  uint8_t pad2[0x70 - 0x18];
  bool ConstructRequest(void** ppRequest);
};
class cTelemetryUploadTransaction : public cITransaction {
 public:
  uint32_t mpTelemetryStream;  // +0x8
  uint64_t mSession;           // +0x10
  bool ConstructRequest(void** ppRequest);
};

// @ 0x0061a650  (asset-feed GET through a cServerResponse)
bool AssetFeedGetRequest(void** ppRequest);
bool AssetFeedGetRequest(void** ppRequest) {
  (void)ppRequest;
  return false;
}

// @ 0x0061aa00
bool cUserMatchTransaction::ConstructRequest(void** ppRequest) {
  (void)ppRequest;
  return false;
}

// @ 0x0061abf0
bool UserMatchGetRequest(void** ppRequest);
bool UserMatchGetRequest(void** ppRequest) {
  (void)ppRequest;
  return false;
}

// @ 0x0061ad70
bool cHandshakeTransaction::ConstructRequest(void** ppRequest) {
  (void)ppRequest;
  return false;
}

// @ 0x0061b0e0
bool cTelemetryUploadTransaction::ConstructRequest(void** ppRequest) {
  (void)ppRequest;
  return false;
}
}  // namespace Pollen
}  // namespace SP
