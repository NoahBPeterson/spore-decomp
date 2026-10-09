// SP::Pollen transactions (YouTube + feed editing) and EASTL helpers. Flags: /O2 /MD /Gy /TP
#include "s00618150.h"

namespace eastl {
// 0x00475ab0 / 0x00455d60 are declared in the header.
}

namespace SP {
namespace Pollen {
using namespace eastl;

class cYouTubeAuthenticationTransaction : public cITransaction {
 public:
  string8 mUsername;  // +0x8
  string8 mPassword;  // +0x18
  string8 mSource;    // +0x28
  bool mCheckRegistration;
  virtual ~cYouTubeAuthenticationTransaction();
  bool ConstructRequest(void** ppRequest);
};
class cYouTubeVideoURLTransaction : public cITransaction {
 public:
  string8 mMyEmailAddress;           // +0x8
  string8 mDestinationEmailAddress;  // +0x18
  string8 mMessageText;              // +0x28
  string8 mLocale;                   // +0x38
  virtual ~cYouTubeVideoURLTransaction();
  bool ConstructRequest(void** ppRequest);
};
class cYouTubeVideoUploadTransaction : public cITransaction {
 public:
  string8 mUsername;             // +0x8
  string8 mClienID;              // +0x18
  string8 mAuthenticationToken;  // +0x28
  string8 mDeveloperKey;         // +0x38
  string8 mVideoFilename;        // +0x48
  uint32_t mVideoKey[3];         // +0x58
  string8 mXMLRequest;           // +0x64
  virtual ~cYouTubeVideoUploadTransaction();
};

// ---- HTTP plumbing (EA::Internet) ----------------------------------------------------------
struct IRef {
  virtual int AddRef();   // +0
  virtual int Release();  // +4
};
struct HTTPRequest {
  uint32_t vtbl;
  long mRefCount;  // +4
  uint32_t pad[0x2f4 / 4 - 2];
  uint32_t mHeaders[1];  // +0x2f4 (header map; see FUN_00944db0)
  uint32_t pad2[(0xd8c - 0x2f8) / 4];
  void* mpBodyStream;     // +0xd8c
  void* mpAsyncRequest;   // +0xd90
  uint32_t mCallbackVtbl;  // +0xd94
};
struct HttpRequestBody {  // base of the two body streams
  virtual ~HttpRequestBody();
  virtual int AddRef();   // +4
  virtual int Release();  // +8
};
#define PVS(n) virtual void pv##n();
struct UrlEncodedBody : HttpRequestBody {  // 0x28 bytes, ctor 0x00946c50
  uint32_t pad[9];
  UrlEncodedBody();
  PVS(3) PVS(4) PVS(5) PVS(6) PVS(7) PVS(8) PVS(9) PVS(10) PVS(11) PVS(12) PVS(13) PVS(14) PVS(15) PVS(16)
  PVS(17)
  virtual bool AddField(const char* name, const char* value);  // +0x48
};
struct MultipartBody : HttpRequestBody {  // 0x48 bytes, ctor 0x00946dc0
  uint32_t pad[17];
  MultipartBody();
  PVS(3) PVS(4) PVS(5) PVS(6) PVS(7) PVS(8) PVS(9) PVS(10) PVS(11) PVS(12) PVS(13) PVS(14) PVS(15) PVS(16)
  PVS(17) PVS(18) PVS(19) PVS(20)
  virtual bool AddField(const char* name, const char* value);  // +0x54
};
struct AsyncRequest {  // Graphics::GraphicsFactoryAsyncRequest, 0x24 bytes
  uint32_t pad[9];
  AsyncRequest(int a, int b, const char* typeName); // 0x0093c270
  void SetPriority(int mode, float f);  // 0x0093bb40
};
template <typename T>
struct Ref {
  T* mpObject;
  Ref(T* p) : mpObject(p) {
    if (mpObject) mpObject->AddRef();
  }
  ~Ref() {
    if (mpObject) mpObject->Release();
  }
  T* operator->() const { return mpObject; }
  operator bool() const { return mpObject != 0; }
};
struct ReqPtr {  // EA::AutoRefCount<HTTPRequest>
  HTTPRequest* mpObject;
  ReqPtr() : mpObject(0) {}
  ~ReqPtr();                   // 0x0060d210
  HTTPRequest** operator&();  // 0x0060d240
};
bool CreateHTTPPostRequest(const char* url, HttpRequestBody* body, AsyncRequest* async, HTTPRequest** out);
void GetServiceURL(void* key, string8* out);  // 0x00621460
extern int gYouTubeAuthURL, gYouTubeEmailURL;

// @ 0x00618150
cYouTubeAuthenticationTransaction::~cYouTubeAuthenticationTransaction() {}

// @ 0x006181c0
bool cYouTubeAuthenticationTransaction::ConstructRequest(void** ppRequest) {
  Ref<UrlEncodedBody> body(new ("Pollinator", 0, 0, 0, 0) UrlEncodedBody());
  if (body) {
    AsyncRequest* async = new ("Pollinator", 0, 0, 0, 0) AsyncRequest(0, 0, "UTF/MemoryStream");
    async->SetPriority(1, 1.0f);
    if (body->AddField("Email", mUsername.mpBegin) &&
        body->AddField("Passwd", mPassword.mpBegin) &&
        body->AddField("service", "youtube") &&
        body->AddField("source", mSource.mpBegin)) {
      string8 url;
      GetServiceURL(&gYouTubeAuthURL, &url);
      ReqPtr req;
      if (CreateHTTPPostRequest(url.mpBegin, body.mpObject, async, &req)) {
        _InterlockedExchangeAdd(&req.mpObject->mRefCount, 1);
        req.mpObject->mCallbackVtbl = 0x015206f0;
        *ppRequest = req.mpObject;
        return true;
      }
    }
  }
  return false;
}

// @ 0x00618370
cYouTubeVideoUploadTransaction::~cYouTubeVideoUploadTransaction() {}

// @ 0x00618430
cYouTubeVideoURLTransaction::~cYouTubeVideoURLTransaction() {}

// @ 0x006184c0
bool cYouTubeVideoURLTransaction::ConstructRequest(void** ppRequest) {
  Ref<MultipartBody> body(new ("Pollinator", 0, 0, 0, 0) MultipartBody());
  if (body) {
    AsyncRequest* async = new ("Pollinator", 0, 0, 0, 0) AsyncRequest(0, 0, "UTF/MemoryStream");
    async->SetPriority(1, 1.0f);
    if (body->AddField("locale", mLocale.mpBegin) &&
        body->AddField("myEmail", mMyEmailAddress.mpBegin) &&
        body->AddField("destEmail", mDestinationEmailAddress.mpBegin) &&
        body->AddField("msgTxt", mMessageText.mpBegin)) {
      string8 url;
      GetServiceURL(&gYouTubeEmailURL, &url);
      ReqPtr req;
      if (CreateHTTPPostRequest(url.mpBegin, body.mpObject, async, &req)) {
        _InterlockedExchangeAdd(&req.mpObject->mRefCount, 1);
        req.mpObject->mCallbackVtbl = 0x015206f0;
        *ppRequest = req.mpObject;
        return true;
      }
    }
  }
  return false;
}

// ---- retail-layout upload request (this+8 is the video stream) --------------------------------
struct IRefObj {
  virtual ~IRefObj();
  virtual int AddRef();
  virtual int Release();
};
struct IStreamLike : IRefObj {
  PVS(3) PVS(4) PVS(5) PVS(6) PVS(7) PVS(8) PVS(9) PVS(10)
  virtual int GetSize();  // +0x2c
};
struct Obj8 : IRefObj {  // 0x8 bytes, ctor 0x0093c430
  uint32_t pad;
  Obj8();
};
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
extern "C" long __cdecl _InterlockedIncrement(long volatile*);
extern "C" long __cdecl _InterlockedDecrement(long volatile*);
#pragma intrinsic(_InterlockedExchange, _InterlockedIncrement, _InterlockedDecrement)
struct UploadRequest {  // retail HTTPRequest, size 0xd98, ctor 0x009442e0
  virtual ~UploadRequest();
  long mRefCount;  // +4
  uint32_t pad[0x2f4 / 4 - 2];
  uint32_t mHeaders[1];  // +0x2f4
  uint32_t pad2[(0xd8c - 0x2f8) / 4];
  IRefObj* mpBody;         // +0xd8c
  IRefObj* mpAsync;        // +0xd90
  uint32_t mCallbackVtbl;  // +0xd94
  UploadRequest();
  void SetMethod(int m);               // 0x009438c0
  void SetURL(const char* url);        // 0x00942f70
  void AddHeader(int id, const char* v);  // 0x00944db0 (on mHeaders)
  void AddRef() { _InterlockedExchangeAdd(&mRefCount, 1); }
  void Release() {
    long n = _InterlockedExchangeAdd(&mRefCount, -1);
    if (--n == 0) {
      _InterlockedExchange(&mRefCount, 1);
      delete this;
    }
  }
};
struct HeaderMap {
  void Add(int id, const char* v);  // 0x00944db0
};
int Sprintf8(char* dst, const char* fmt, ...);  // 0x00938470
struct IMessageServer {
  PVS(0) PVS(1) PVS(2) PVS(3) PVS(4)
  virtual void PostMSG(uint32_t id, void* p1, void* p2);  // +0x14
};
IMessageServer* GetMessageServer();  // 0x0067dcc0
extern uint32_t gMsgUploadFailed;    // 0x060ba744

class cUploadTransactionRetail {
 public:
  uint32_t pad[2];
  IStreamLike* mpStream;  // +0x8
  bool ConstructRequest(void** ppRequest);
};

// @ 0x00618670
bool cUploadTransactionRetail::ConstructRequest(void** ppRequest) {
  if (mpStream) {
    string8 url;
    GetServiceURL(&gMsgUploadFailed, &url);
    Ref<UploadRequest> req(new ("Pollinator", 0, 0, 0, 0) UploadRequest());
    req->SetMethod(4);
    req->SetURL(url.mpBegin);
    Obj8* o = new ("Pollinator", 0, 0, 0, 0) Obj8();
    IRefObj* oldAsync = req->mpAsync;
    if (o != oldAsync) {
      if (o) o->AddRef();
      IRefObj* old = oldAsync;
      req->mpAsync = o;
      if (old) old->Release();
    }
    IStreamLike* pStream = mpStream;
    IRefObj* oldBody = req->mpBody;
    if (pStream != oldBody) {
      if (pStream) pStream->AddRef();
      IRefObj* old = oldBody;
      req->mpBody = pStream;
      if (old) old->Release();
    }
    int n = mpStream->GetSize();
    if (n != -1) {
      uint32_t buf[16];
      Sprintf8((char*)buf, "%d", n);
      ((HeaderMap*)req->mHeaders)->Add(0x26, (char*)buf);
      ((HeaderMap*)req->mHeaders)->Add(0x2a, "text/xml");
      req->AddRef();
      req->mCallbackVtbl = 0x015206f0;
      *ppRequest = req.mpObject;
      return true;
    }
  }
  GetMessageServer()->PostMSG(0x060ba744, 0, 0);
  return false;
}

}  // namespace Pollen
}  // namespace SP

// ---- EASTL helpers ---------------------------------------------------------------------------
int Vsnprintf8(char* dst, unsigned int cap, const char* fmt, void* args);  // 0x00938400
namespace eastl {
template <typename T>
inline const T& max_alt(const T& a, const T& b) { return a < b ? b : a; }
// @ 0x00618890
string8 operator+(const string8& a, const string8& b) {
  string8 result(string8::CtorDoNotInitialize(), a.size() + b.size());
  result.append(a);
  result.append(b);
  return result;
}

// @ 0x006188f0
template <>
string8& string8::append_sprintf_va_list(const char* pFormat, void* arguments) {
  const int nInitialSize = (int)(mpEnd - mpBegin);
  int nCount;
  if (mpBegin == gEmptyString)
    nCount = Vsnprintf8(mpEnd, 0, pFormat, arguments);
  else
    nCount = Vsnprintf8(mpEnd, (unsigned int)(mpCapacity - mpEnd), pFormat, arguments);
  if (nCount >= (int)(mpCapacity - mpEnd)) {
    set_capacity(nInitialSize + nCount);
    nCount = Vsnprintf8(mpBegin + nInitialSize, (unsigned int)(nCount + 1), pFormat, arguments);
  } else if (nCount < 0) {
    unsigned int nCapacity = max_alt((unsigned int)7, (unsigned int)(mpEnd - mpBegin) * 2);
    for (; (nCount < 0) && (nCapacity < 1000000); nCapacity *= 2) {
      set_capacity(nCapacity);
      nCount = Vsnprintf8(mpBegin + nInitialSize, nCapacity - nInitialSize + 1, pFormat, arguments);
    }
  }
  if (nCount >= 0) mpEnd = mpBegin + nInitialSize + nCount;
  return *this;
}
}  // namespace eastl

// ---- sorted index heap helpers (indices into 0x118-byte entries, descending by 64-bit key) ------
namespace SP {
namespace Pollen {
struct AtomEntry {  // 0x118 bytes
  uint32_t pad0[12];
  int64_t mKey;  // +0x30
  uint32_t pad1[(0xb8 - 0x38) / 4];
  const char* mURL;  // +0xb8
  uint32_t pad2[(0x118 - 0xbc) / 4];
};
struct AtomDocument {
  virtual ~AtomDocument();
  int mRefCount;  // +4
  uint32_t pad[(0x60 - 8) / 4];
  AtomEntry* mpEntriesBegin;  // +0x60
  AtomEntry* mpEntriesEnd;    // +0x64
  uint32_t pad2[(0xb8 - 0x68) / 4];
  void Release() {
    int n = (*(volatile int*)&mRefCount += -1);
    if (n == 0) {
      mRefCount = 1;
      delete this;
    }
  }
};
struct EntryKeyGreater {
  AtomDocument* mpDoc;
  bool operator()(unsigned int a, unsigned int b) const {
    return mpDoc->mpEntriesBegin[a].mKey > mpDoc->mpEntriesBegin[b].mKey;
  }
};
void AdjustHeap(unsigned int* first, int topPosition, int heapSize, int position, unsigned int value,
                EntryKeyGreater cmp);  // 0x00617530

// @ 0x006189e0
unsigned int* UnguardedPartition(unsigned int* first, unsigned int* last, unsigned int pivot,
                                 EntryKeyGreater cmp) {
  for (;;) {
    while (cmp(*first, pivot)) ++first;
    --last;
    while (cmp(pivot, *last)) --last;
    if (!(first < last)) return first;
    unsigned int t = *first;
    *first = *last;
    *last = t;
    ++first;
  }
}

// @ 0x00618a60
void make_heap(unsigned int* first, unsigned int* last, EntryKeyGreater cmp) {
  const int heapSize = (int)(last - first);
  if (heapSize >= 2) {
    int parentPosition = ((heapSize - 2) >> 1) + 1;
    do {
      --parentPosition;
      unsigned int temp = *(first + parentPosition);
      AdjustHeap(first, parentPosition, heapSize, parentPosition, temp, cmp);
    } while (parentPosition != 0);
  }
}

// @ 0x00618aa0
void sort_heap(unsigned int* first, unsigned int* last, EntryKeyGreater cmp) {
  for (; (last - first) > 1; --last) {
    unsigned int tempBottom = *(last - 1);
    *(last - 1) = *first;
    AdjustHeap(first, 0, (int)(last - first - 1), 0, tempBottom, cmp);
  }
}
}  // namespace Pollen
}  // namespace SP

// ---- misc -----------------------------------------------------------------------------------
namespace SP {
namespace Pollen {
// A string whose allocator is a single name dword at +0x10 (copy ctor at 0x00618af0).
struct NamedAlloc {
  uint32_t mName;
  NamedAlloc() {}
  NamedAlloc(const NamedAlloc& x) : mName(x.mName) {}
};
struct string8N {
  char* mpBegin;
  char* mpEnd;
  char* mpCapacity;
  uint32_t mPad;
  NamedAlloc mAllocator;
  void AllocateSelf(unsigned int n);  // 0x00616aa0
  static char* CharStringUninitializedCopy(const char* pSource, const char* pSourceEnd, char* pDestination) {
    memcpy(pDestination, pSource, (unsigned int)(pSourceEnd - pSource));
    return pDestination + (pSourceEnd - pSource);
  }
  void RangeInitialize(const char* pBegin, const char* pEnd) {
    const unsigned int n = (unsigned int)(pEnd - pBegin);
    AllocateSelf(n + 1);
    mpEnd = CharStringUninitializedCopy(pBegin, pEnd, mpBegin);
    *mpEnd = 0;
  }
  // @ 0x00618af0
  string8N(const string8N& x);
};
string8N::string8N(const string8N& x) : mpBegin(0), mpEnd(0), mpCapacity(0), mAllocator(x.mAllocator) {
  RangeInitialize(x.mpBegin, x.mpEnd);
}

// ---- Message strings -------------------------------------------------------------------------
struct IMsgBaseA {
  virtual void a0();
};
struct IMsgBaseB {
  IMsgBaseB() { _InterlockedExchange(&mRefCount, 0); }
  virtual void b0();
  long mRefCount;
};
struct cMsgString8 : IMsgBaseA, IMsgBaseB {
  string8 mString;  // +0xc
  virtual int AddRef();
  virtual int Release();
  static void operator delete(void* p) { EASTL_allocator_deallocate(p); }
  virtual ~cMsgString8();
  cMsgString8(const char* s) : mString(string8::CtorZero()) { mString.RangeInit(s); }
};
struct IRef2 {
  virtual int AddRef();
  virtual int Release();
};
struct MsgSlot {
  IRef2* mpObject;
  uint32_t mPad;
};
struct MsgHolder {  // +8: slots[idx], +0x38: bitmask of live slots
  uint32_t pad[2];
  MsgSlot mSlots[6];
  uint32_t mMask;
};

// @ 0x00618b90
// scalar deleting destructor of cMsgString8
cMsgString8::~cMsgString8() {}

// @ 0x00618bd0
void SetMessageString8(MsgHolder* holder, int idx, const char* str) {
  cMsgString8* msg = new ("App", 0, 0, 0, 0) cMsgString8(str);
  uint32_t bit = 1u << idx;
  if (holder->mMask & bit) {
    if (holder->mSlots[idx].mpObject) holder->mSlots[idx].mpObject->Release();
  }
  holder->mSlots[idx].mpObject = (IRef2*)msg;
  if (msg) ((IRef2*)msg)->AddRef();
  holder->mMask |= bit;
}
}  // namespace Pollen
}  // namespace SP

// ---- feed info / feed transactions ---------------------------------------------------------------
unsigned int FNVHash(const char* s, unsigned int seed, int lowercase);  // 0x00932e80
int GetFeedTypeFromURI(const char* uri);                                // 0x005419c0
namespace SP {
namespace Pollen {
struct FeedAuthor {  // pointed to by FeedSource::mpAuthor
  uint32_t pad[2];
  string16 mName;  // +0x8
  uint32_t mId0;   // +0x18
  uint32_t mId1;   // +0x1c
};
struct FeedSource {  // source record
  uint32_t pad0[2];
  string8 mURI;       // +0x8
  uint32_t pad1[1];
  string16 mTitle;    // +0x1c
  string16 mDesc;     // +0x2c
  uint32_t pad2[1];
  uint32_t mKey[3];   // +0x40
  FeedAuthor* mpAuthor;  // +0x4c
  string8 mExtra;     // +0x50
};
struct FeedInfo {  // destination record
  string16 mAuthorName;  // +0x0
  uint32_t mAuthorId0;   // +0x10
  uint32_t mAuthorId1;   // +0x14
  string16 mTitle;       // +0x18
  string16 mDesc;        // +0x28
  uint32_t mKey[3];      // +0x38
  string8 mExtra;        // +0x44
  string8 mURI;          // +0x54
  uint32_t mURIHash;     // +0x64
  int mFeedType;         // +0x68
};

// @ 0x00618c70
void FillFeedInfo(const FeedSource* src, FeedInfo* dst) {
  dst->mURI = src->mURI;
  dst->mURIHash = FNVHash(dst->mURI.mpBegin, 0x811c9dc5, 1);
  dst->mTitle = src->mTitle;
  dst->mDesc = src->mDesc;
  dst->mKey[0] = src->mKey[0];
  dst->mKey[1] = src->mKey[1];
  dst->mKey[2] = src->mKey[2];
  dst->mExtra = src->mExtra;
  dst->mFeedType = GetFeedTypeFromURI(src->mURI.mpBegin);
  if (src->mpAuthor) {
    dst->mAuthorName = src->mpAuthor->mName;
    dst->mAuthorId0 = src->mpAuthor->mId0;
    dst->mAuthorId1 = src->mpAuthor->mId1;
  }
}

struct FixedPtrVector {  // fixed_vector<void*, 40> (+0x30 in the retail transaction)
  void** mpBegin;
  void** mpEnd;
  void** mpCapacity;
  uint32_t pad[2];
  uint32_t mOverflow;
  uint32_t mBuffer[40];
  FixedPtrVector() : mpBegin((void**)mBuffer), mpEnd((void**)mBuffer), mpCapacity((void**)mBuffer + 40), mOverflow(0) {}
};
class cFeedTransactionBase : public cITransaction {  // retail layout, size 0xec
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
  cFeedTransactionBase(uint32_t type, uint32_t intParam, uint32_t count, uint32_t unk18);
  cFeedTransactionBase(uint32_t type, const char* str, uint32_t intParam);
  virtual ~cFeedTransactionBase();  // 0x00617a40
};
// @ 0x00618d40
cFeedTransactionBase::cFeedTransactionBase(uint32_t type, uint32_t intParam, uint32_t count, uint32_t unk18)
    : mpFeed(0), mFeedType(type), mnIntParam(intParam), mnCount(count), mUnk18(unk18), mFlag(0) {
}
// @ 0x00618da0
cFeedTransactionBase::cFeedTransactionBase(uint32_t type, const char* str, uint32_t intParam)
    : mpFeed(0), mFeedType(type), mnIntParam(intParam), mnCount(0xffffffff), mUnk18(0),
      mStringParam(string8::CtorZero()), mFlag(0) {
  mStringParam.RangeInit(str);
}

extern void* gFreeListGetAsset;  // 0x015f5488
extern void* gFreeListGetAssetEx;  // 0x015f55b0
class cGetAssetFeedTransaction : public cFeedTransactionBase {
 public:
  static void operator delete(void* p) {
    *(void**)p = gFreeListGetAsset;
    gFreeListGetAsset = p;
  }
  virtual ~cGetAssetFeedTransaction();
};
// @ 0x00618e00 (scalar deleting destructor)
cGetAssetFeedTransaction::~cGetAssetFeedTransaction() {}

struct OwnedBuffer {
  void* mp;
  ~OwnedBuffer() {
    if (mp) EASTL_allocator_deallocate(mp);
  }
};
class cGetAssetFeedTransactionEx : public cFeedTransactionBase {
 public:
  uint32_t pad[(0xf8 - 0xec) / 4];
  OwnedBuffer mBuffer;  // +0xf8
  static void operator delete(void* p) {
    *(void**)p = gFreeListGetAssetEx;
    gFreeListGetAssetEx = p;
  }
  virtual ~cGetAssetFeedTransactionEx();
};
// @ 0x00618e30
cGetAssetFeedTransactionEx::~cGetAssetFeedTransactionEx() {}

// ---- cEditFeedTransaction --------------------------------------------------------------------
struct hash_set_u64 {  // eastl::hash_set<uint64_t>, size 0x20
  uint32_t mfRehash;      // +0
  void** mpBucketArray;   // +4
  uint32_t mnBucketCount;  // +8
  uint32_t mnElementCount;  // +0xc
  uint32_t pad[4];
  void DoFreeNodes(void** pArr, uint32_t n);  // 0x005687d0
  void clear() {
    DoFreeNodes(mpBucketArray, mnBucketCount);
    mnElementCount = 0;
  }
  ~hash_set_u64() {
    clear();
    if (mnBucketCount > 1) EASTL_allocator_deallocate(mpBucketArray);
  }
};
template <typename T>
struct AutoRefDoc {
  T* mpObject;
  AutoRefDoc() : mpObject(0) {}
  void reset() {
    if (mpObject) {
      T* const pTemp = mpObject;
      mpObject = 0;
      pTemp->Release();
    }
  }
  ~AutoRefDoc() {
    if (mpObject) mpObject->Release();
  }
};
class cEditFeedTransaction : public cITransaction {
 public:
  AutoRefDoc<AtomDocument> mpFeed;  // +0x8
  uint32_t mOpType;                 // +0xc
  string8 mFeedURI;                 // +0x10
  string8 mFeedDescription;         // +0x20
  hash_set_u64 mAssetsToAdd;        // +0x30
  hash_set_u64 mAssetsToRemove;     // +0x50
  virtual ~cEditFeedTransaction();
  bool ConstructRequest(void** ppRequest);
};
// @ 0x00618e70
cEditFeedTransaction::~cEditFeedTransaction() { mpFeed.reset(); }

// ---- a feed-entry asset download (retail layout: +8 feed, +0xc entry index, +0x10 key) --------------------
struct DownloadSession {  // 0x42d0 bytes, ctor 0x005cbec0
  uint32_t pad[0x42d0 / 4];
  DownloadSession();
  void Bind(void* target);  // 0x005cbd30
};
struct DownloadTarget {  // 0xac bytes, ctor 0x004b9c70
  uint32_t pad[0xac / 4];
  DownloadTarget();
};
struct TargetRef {  // EA::AutoRefCount<DownloadTarget>
  DownloadTarget* mp;
  void Set(DownloadTarget* p);  // 0x00b5f950
};
struct SessionRef {  // EA::AutoRefCount<DownloadSession>
  DownloadSession* mp;
  void Set(DownloadSession* p);  // 0x00572620
};
void* GetSaveArea(uint32_t id);  // 0x006b1f90
bool CreateHTTPGetRequest(const char* url, void* stream, HTTPRequest** out);  // 0x00944450
struct HTTPRequestEx : HTTPRequest {
  void SetProperty(string8* name, void* value);  // 0x00944a10
};

class cFeedEntryAssetTransaction : public cITransaction {
 public:
  AtomDocument* mpFeed;  // +0x8
  uint32_t mIndex;       // +0xc
  uint32_t mKey[3];      // +0x10
  SessionRef mSession;   // +0x1c
  TargetRef mTarget;     // +0x20
  bool ConstructRequest(void** ppRequest);
};
struct ReqPtrEx {
  HTTPRequestEx* mpObject;
  ReqPtrEx() : mpObject(0) {}
  ~ReqPtrEx();                  // 0x0060d210
  HTTPRequestEx** operator&();  // 0x0060d240
};

// @ 0x00618f60
bool cFeedEntryAssetTransaction::ConstructRequest(void** ppRequest) {
  AtomDocument* doc = mpFeed;
  if (doc) {
    if (mIndex <= (unsigned int)(doc->mpEntriesEnd - doc->mpEntriesBegin)) {
      AtomEntry* entry = doc->mpEntriesBegin + mIndex;
      if (GetSaveArea(0x11ac19d)) {
        mTarget.Set(new ("Pollinator", 0, 0, 0, 0) DownloadTarget());
        mSession.Set(new ("Pollinator", 0, 0, 0, 0) DownloadSession());
        mSession.mp->Bind(mTarget.mp);
        uint32_t* dst = (uint32_t*)((char*)mTarget.mp + 8);
        dst[0] = mKey[0];
        dst[1] = mKey[1];
        dst[2] = mKey[2];
        void* stream = mSession.mp ? (char*)mSession.mp + 8 : 0;
        ReqPtrEx req;
        if (CreateHTTPGetRequest(entry->mURL, stream, (HTTPRequest**)&req)) {
          _InterlockedExchangeAdd(&req.mpObject->mRefCount, 1);
          {
            string8 ctx("context");
            req.mpObject->SetProperty(&ctx, (char*)mpFeed + 8);
          }
          req.mpObject->mCallbackVtbl = 0x015206f0;
          *ppRequest = req.mpObject;
        }
        return true;
      }
    }
  }
  return false;
}
}  // namespace Pollen
}  // namespace SP
// --- equivalence checker address annotations
    void* operator new(unsigned int, char*, int, unsigned int, char*, int); // 0x00f473a0

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct AsyncRequest {
    AsyncRequest(int, int, char*); // 0x0093c270
};
}
