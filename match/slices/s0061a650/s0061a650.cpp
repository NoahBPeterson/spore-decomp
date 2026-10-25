// Slice s0061a650: SP::Pollen feed/YouTube/telemetry transaction constructors and request
// builders. Flags: /O2 /MD /Gy /TP (no /EHsc).
#include "../s00622f20/s00622f20.h"

extern "C" unsigned int __cdecl strlen(const char*);
#pragma intrinsic(strlen)

// eastl::basic_string<char>::basic_string(CtorSprintf, const char*, ...)
void CtorSprintfU64(string8* out, int tag, const char* format, ...);  // 0x00472F50

extern void* vtGetAssetFeedTransaction[];    // 0x013FC604
extern void* vtGetAssetFeedTransactionEx[];  // 0x013FC628
struct VtblPtr { void* vptr; };

namespace EA {
namespace Internet {
struct HTTPHeaders {
  bool AddHeaderEntry(const char* name, const char** value);    // 0x00944cb0
  bool AddHeaderEntryField(int field, const char** value);      // 0x00944d50
};
}  // namespace Internet
}  // namespace EA

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
  cFeedTransactionBase(uint32_t type, const char* str, uint32_t intParam);  // 0x00618DA0
};

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
  ((VtblPtr*)this)->vptr = vtGetAssetFeedTransaction;
  string8 tmp;
  CtorSprintfU64(&tmp, 0, "%I64u", lo, hi);
  mStringParam.assign(tmp.mpBegin, tmp.mpEnd);
  mFlag = 1;
}

// @ 0x0061a8b0
cGetAssetFeedTransactionEx::cGetAssetFeedTransactionEx(uint32_t lo, uint32_t hi)
    : cFeedTransactionBase(3, (const char*)0x013ec47c, 0), mId((uint64_t)lo | ((uint64_t)hi << 32)) {
  ((VtblPtr*)this)->vptr = vtGetAssetFeedTransactionEx;
  mExtra.mpBegin = 0;
  mExtra.mpEnd = 0;
  mExtra.mpCapacity = 0;
  string8 tmp;
  CtorSprintfU64(&tmp, 0, "%I64u", lo, hi);
  mStringParam.assign(tmp.mpBegin, tmp.mpEnd);
  mFlag = 1;
}

// @ 0x0061a970
cEditFeedTransaction::cEditFeedTransaction(int opType)
    : mpFeed(0), mOpType(opType), mFeedURI(), mFeedDescription(), mAssetsToAdd(), mAssetsToRemove() {}

// ---------------------------------------------------------------------------------------------
// Request builders. Each one looks a service URL up in the Pollen URL map, creates an
// EA::Internet GET request, decorates it with parameters/headers and hands a reference back
// through ppRequest. Flags on failure are released through the same refcount helpers.
// ---------------------------------------------------------------------------------------------
extern "C" long __cdecl _InterlockedExchangeAdd(long volatile*, long);
#pragma intrinsic(_InterlockedExchangeAdd)

// SP::Pollen::MapLookup (0x00621460) and eastl::basic_string<char>::append_sprintf (0x005f9450).
// Both are variadic, so the compiler passes their `this` as the first stack argument.
void MapLookup(uint32_t hash, string8* out);                 // 0x00621460
void append_sprintf(string8* out, const char* format, ...);  // 0x005f9450

// Retail response-callback vtable installed at HTTPRequest+0xd94.
extern void* gResponseCallbacks[];  // 0x015206f0

class cAssetMetadata {
 public:
  const uint64_t& GetAssetID() const;  // 0x005507a0
};

// Refcounted object with the deleting destructor in vtable slot 0 and the count at +4.
struct RefCounted {
  virtual void* Destroy(unsigned int flags);
  long mnRef;  // +0x4
  void AddRef() { _InterlockedExchangeAdd(&mnRef, 1); }
  void Release() {
    if (_InterlockedExchangeAdd(&mnRef, -1) == 1) {
      _InterlockedExchange(&mnRef, 1);
      Destroy(1);
    }
  }
};

// Refcounted helper object whose AddRef/Release live in vtable slots 1 and 2.
struct VRefCounted {
  virtual void* Destroy(unsigned int flags);  // slot 0
  virtual int AddRef();                       // slot 1
  virtual int Release();                      // slot 2
  long mnRef;                                 // +0x4
};

struct IResponseHandler : VRefCounted {};
struct cHTTPResponseHandler : IResponseHandler {
  cHTTPResponseHandler* Ctor();  // 0x0093c430
};

class cServerResponse : public EA::RefCountVTemplate<int> {
 public:
  cServerResponse* Ctor();  // 0x00615790
  bool Open();              // 0x00615450
  IResponseHandler mHandler;  // +0x8
};

namespace Feed {
class HandshakeParser : public VRefCounted {
 public:
  HandshakeParser* Ctor();  // 0x005453c0
  void SetLists(void* list14, void* list28, void* list3c, void* list50);  // 0x00545620
  bool Open();  // 0x00545710
  char mStream;  // +0x8
};
}  // namespace Feed

struct TelemetryStream : VRefCounted {
  virtual int Slot3();
  virtual int Slot4();
  virtual int Slot5();
  virtual int Slot6();
  virtual int GetSize();  // slot 7, +0x1c
};

// UTFInternet::HTTPRequest: refcount at +4, URL/headers/body streams follow, response handler
// and callback table at the tail.
struct HTTPRequest : RefCounted {
  uint8_t mReserved0[0x2f4 - 8];
  EA::Internet::HTTPHeaders mHeaders;                 // +0x2f4
  uint8_t mReserved1[0xd8c - 0x2f5];
  TelemetryStream* mpStream;                          // +0xd8c
  IResponseHandler* mpHandler;                        // +0xd90
  const void* mpCallbacks;                            // +0xd94
  HTTPRequest* Construct();                           // 0x009442e0
  void SetURL(const char* url);                       // 0x00942f70
  void SetMethod(int method);                         // 0x009438c0
  bool AddRequestParameter(const char* name, const char* value);  // 0x00944660
};

bool CreateHTTPGetRequest(const char* url, void* stream, HTTPRequest** out);  // 0x00944450
bool ConvertPathToEncodedForm(const char* url, string8& encoded, string8* out);  // 0x0094b610
void Iterate2(void* keys, void* names);  // 0x00687a20

// Intrusive request holder: one reference is held while mpObject is non-null.
struct RequestRef {
  HTTPRequest* mpObject;
  RequestRef() : mpObject(0) {}
  ~RequestRef() { Release(); }
  void Release() {
    HTTPRequest* p = mpObject;
    if (p) {
      if (_InterlockedExchangeAdd(&p->mnRef, -1) == 1) {
        _InterlockedExchange(&p->mnRef, 1);
        p->Destroy(1);
      }
    }
  }
  HTTPRequest** Out() {
    if (mpObject) {
      HTTPRequest* p = mpObject;
      mpObject = 0;
      if (_InterlockedExchangeAdd(&p->mnRef, -1) == 1) {
        _InterlockedExchange(&p->mnRef, 1);
        p->Destroy(1);
      }
    }
    return &mpObject;
  }
  void AddRef() { _InterlockedExchangeAdd(&mpObject->mnRef, 1); }
  HTTPRequest* operator->() const { return mpObject; }
};

// HTTPHeaders::AddHeaderEntry* take a pointer to the string's character pointer.
static inline const char** StringValuePtr(string8& str) { return (const char**)&str.mpBegin; }

// EASTL vector blocks carry their element count in the four bytes before the data.
template <typename T>
static inline void FreeCountedArray(T* data) {
  if (data && reinterpret_cast<int*>(data)[-1] != 0) EASTL_allocator_deallocate(data);
}

class cAssetFeedRequestBuilder {
 public:
  uint32_t mReserved0[5];
  cAssetMetadata* mpMetadata;  // +0x14
  bool AssetFeedGetRequest(void** ppRequest);
};

class cUserMatchTransaction : public cITransaction {
 public:
  uint64_t mAssetID;  // +0x8
  bool mbRating;      // +0x10
  bool ConstructRequest(void** ppRequest);
  bool UserMatchGetRequest(void** ppRequest);
};

struct HandshakeList {
  void* mpBegin;        // +0x0
  void* mpEnd;          // +0x4
  void* mpCapacity;     // +0x8
  uint32_t mAllocator;  // +0xc
  uint32_t mAllocatorPad;  // +0x10
};
struct AddOnNameList {  // eastl::vector<string16> filled by Iterate2
  string16* mpBegin;     // +0x0
  string16* mpEnd;       // +0x4
  string16* mpCapacity;  // +0x8
  uint32_t mAllocator;   // +0xc
  void DoDestroyValues(string16* first, string16* last);  // 0x0084aad0
};
struct AddOnIdList {  // eastl::vector<uint32_t> filled by Iterate2
  uint32_t* mpBegin;     // +0x0
  uint32_t* mpEnd;       // +0x4
  uint32_t* mpCapacity;  // +0x8
  uint32_t mAllocator;   // +0xc
};

class cHandshakeTransaction : public cITransaction {
 public:
  void* mpUserData;    // +0x8
  void* mpSessionData; // +0xc
  uint32_t mReserved10;  // +0x10
  HandshakeList mList14;  // +0x14
  HandshakeList mList28;  // +0x28
  HandshakeList mList3c;  // +0x3c
  HandshakeList mList50;  // +0x50
  uint32_t mReserved64[3];  // +0x64
  uint32_t mFlags70;        // +0x70
  uint32_t mReserved74;     // +0x74
  string8 mUser;            // +0x78
  string8 mPassword;        // +0x88
  string8 mProductCode;     // +0x98
  bool ConstructRequest(void** ppRequest);
};

class cTelemetryUploadTransaction : public cITransaction {
 public:
  TelemetryStream* mpTelemetryStream;  // +0x8
  uint64_t mSession;                   // +0x10
  bool ConstructRequest(void** ppRequest);
};

// @ 0x0061a650  (asset-feed GET through a cServerResponse)
bool cAssetFeedRequestBuilder::AssetFeedGetRequest(void** ppRequest) {
  string8 url;
  MapLookup(0x68cb17d, &url);
  append_sprintf(&url, "%lld", mpMetadata->GetAssetID());

  RequestRef request;
  if (!CreateHTTPGetRequest(url.mpBegin, 0, &request.mpObject)) return false;

  void* mem = operator new(0x60, "Pollinator", 0, 0, 0, 0);
  EA::AutoRefCount<cServerResponse> response(mem ? ((cServerResponse*)mem)->Ctor() : 0);
  response->Open();
  IResponseHandler* handler = response.mpObject ? &response.mpObject->mHandler : 0;
  IResponseHandler* oldHandler = request->mpHandler;
  if (handler != oldHandler) {
    if (handler) handler->AddRef();
    request->mpHandler = handler;
    if (oldHandler) oldHandler->Release();
  }
  request->mpCallbacks = gResponseCallbacks;
  request.AddRef();
  *ppRequest = request.mpObject;
  return true;
}

// @ 0x0061aa00
bool cUserMatchTransaction::ConstructRequest(void** ppRequest) {
  string8 url;
  MapLookup(0xf8671bdb, &url);

  RequestRef request;
  void* mem = operator new(8, "Pollinator", 0, 0, 0, 0);
  cHTTPResponseHandler* stream = mem ? ((cHTTPResponseHandler*)mem)->Ctor() : 0;
  if (!CreateHTTPGetRequest(url.mpBegin, stream, request.Out())) {
    if (stream) stream->Release();
    return false;
  }

  request->mpCallbacks = gResponseCallbacks;
  string8 assetIdText;
  CtorSprintfU64(&assetIdText, 0, "%I64u", mAssetID);
  request->AddRequestParameter("assetId", assetIdText.mpBegin);
  request->AddRequestParameter("rating", mbRating ? "1" : "0");
  request.AddRef();
  *ppRequest = request.mpObject;
  return true;
}

// @ 0x0061abf0
bool cUserMatchTransaction::UserMatchGetRequest(void** ppRequest) {
  string8 url;
  MapLookup(0x5efa12b, &url);
  append_sprintf(&url, "%llu", mAssetID);

  RequestRef request;
  void* mem = operator new(8, "Pollinator", 0, 0, 0, 0);
  cHTTPResponseHandler* stream = mem ? ((cHTTPResponseHandler*)mem)->Ctor() : 0;
  if (!CreateHTTPGetRequest(url.mpBegin, stream, request.Out())) {
    if (stream) stream->Release();
    return false;
  }

  request->mpCallbacks = gResponseCallbacks;
  request.AddRef();
  *ppRequest = request.mpObject;
  return true;
}

// @ 0x0061ad70
bool cHandshakeTransaction::ConstructRequest(void** ppRequest) {
  if (!mpUserData || !mpSessionData) return false;

  void* mem = operator new(0x4c, "Pollinator", 0, 0, 0, 0);
  EA::AutoRefCount<Feed::HandshakeParser> parser(mem ? ((Feed::HandshakeParser*)mem)->Ctor() : 0);
  mFlags70 = 0xf;
  parser->SetLists(&mList14, &mList28, &mList3c, &mList50);
  parser->Open();

  string8 url;
  MapLookup(0x539f4e1, &url);

  RequestRef request;
  void* stream = parser ? &parser->mStream : 0;
  if (!CreateHTTPGetRequest(url.mpBegin, stream, request.Out())) return false;

  request->mpCallbacks = gResponseCallbacks;
  request.AddRef();

  ConvertPathToEncodedForm(mUser.mpBegin, mUser, 0);
  request->mHeaders.AddHeaderEntry("Spore-User", StringValuePtr(mUser));
  ConvertPathToEncodedForm(mPassword.mpBegin, mPassword, 0);
  request->mHeaders.AddHeaderEntry("Spore-Password", StringValuePtr(mPassword));
  if (mProductCode.mpBegin != mProductCode.mpEnd)
    request->mHeaders.AddHeaderEntry("Spore-ProductCode", StringValuePtr(mProductCode));

  AddOnNameList names = {};
  AddOnIdList ids = {};
  Iterate2(&names, &ids);
  if (names.mpBegin != names.mpEnd) {
    string8 keysText;
    append_sprintf(&keysText, "0x%08x=%ls", ids.mpBegin[0], names.mpBegin[0]);
    const int count = (int)(names.mpEnd - names.mpBegin);
    for (int i = 1; i < count; ++i)
      append_sprintf(&keysText, ",0x%08x=%ls", ids.mpBegin[i], names.mpBegin[i]);
    request->AddRequestParameter("AddOnKeys", keysText.mpBegin);
  }
  *ppRequest = request.mpObject;

  names.DoDestroyValues(names.mpBegin, names.mpEnd);
  FreeCountedArray(names.mpBegin);
  FreeCountedArray(ids.mpBegin);
  return true;
}

// @ 0x0061b0e0
bool cTelemetryUploadTransaction::ConstructRequest(void** ppRequest) {
  void* mem = operator new(0xd98, "Pollinator", 0, 0, 0, 0);
  if (!mem) return false;
  HTTPRequest* created = ((HTTPRequest*)mem)->Construct();
  if (!created) return false;

  RequestRef request;
  request.mpObject = created;
  request.AddRef();

  string8 url;
  MapLookup(0x539f953, &url);
  created->SetURL(url.mpBegin);
  created->SetMethod(4);

  TelemetryStream* oldStream = created->mpStream;
  if (mpTelemetryStream != oldStream) {
    if (mpTelemetryStream) mpTelemetryStream->AddRef();
    created->mpStream = mpTelemetryStream;
    if (oldStream) oldStream->Release();
  }

  string8 contentType;
  contentType.assign("application/octet-stream");
  created->mHeaders.AddHeaderEntryField(0x2a, StringValuePtr(contentType));

  string8 sizeText;
  CtorSprintfU64(&sizeText, 0, "%d", mpTelemetryStream->GetSize());
  created->mHeaders.AddHeaderEntryField(0x26, StringValuePtr(sizeText));

  string8 sessionText;
  CtorSprintfU64(&sessionText, 0, "%llu", mSession);
  created->mHeaders.AddHeaderEntry("Game-Session-ID", StringValuePtr(sessionText));

  request.AddRef();

  void* handlerMem = operator new(8, "Pollinator", 0, 0, 0, 0);
  IResponseHandler* handler = handlerMem ? ((cHTTPResponseHandler*)handlerMem)->Ctor() : 0;
  IResponseHandler* oldHandler = created->mpHandler;
  if (handler != oldHandler) {
    if (handler) handler->AddRef();
    created->mpHandler = handler;
    if (oldHandler) oldHandler->Release();
  }
  created->mpCallbacks = gResponseCallbacks;
  *ppRequest = created;
  return true;
}
}  // namespace Pollen
}  // namespace SP
