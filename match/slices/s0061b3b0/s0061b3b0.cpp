// Slice s0061b3b0: SP::Pollen YouTube transactions, request/asset helpers, EASTL sort internals
// and a pair of eastl::basic_string / eastl::vector member functions.
// Flags: /O2 /MD /Gy /TP /arch:SSE (no /EHsc).
#include "../s00622f20/s00622f20.h"

extern "C" void EASTL_allocator_deallocate(void* p);  // 0x00f47380
extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags,
                                          unsigned debugFlags, const char* file,
                                          int line);  // 0x00f473a0
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
extern "C" long __cdecl _InterlockedExchange(long volatile*, long);
extern "C" long __cdecl _InterlockedExchangeAdd(long volatile*, long);
#pragma intrinsic(_InterlockedExchange, _InterlockedExchangeAdd)
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);
extern "C" void* __cdecl memmove(void*, const void*, unsigned int);
extern "C" int __cdecl sscanf(const char* s, const char* fmt, ...);

void* operator new(unsigned int size, const char* name, int flags, unsigned debugFlags,
                   const char* file, int line);  // 0x00f473a0
void operator delete(void* p);                       // 0x00f47380

void SetMessageString8(void* holder, int idx, const char* str);  // 0x00618bd0
void* Fun_00614e50(const char* fmt, ...);                        // 0x00614e50

namespace SP {
namespace Pollen {

// =============================================================================================
// A 0x10-byte eastl::basic_string<char> (three pointers + allocator).
struct String8S {
  char* mpBegin;         // +0x00
  char* mpEnd;           // +0x04
  char* mpCapacity;      // +0x08
  unsigned int mAlloc;   // +0x0c
  String8S() {
    mpBegin = gEmptyString;
    mpEnd = gEmptyString;
    mpCapacity = gEmptyString + 1;
  }
  void range_init(const char* p);      // 0x0057cc10
  void sprintf(const char* fmt, ...);  // 0x00472fe0
  void assign(const char* b, const char* e);      // 0x00454cb0
  void append_sprintf(const char* fmt, ...);      // 0x005f9450
  void clear() {
    if (mpBegin != mpEnd) {
      *mpBegin = 0;
      mpEnd = mpBegin;
    }
  }
};
struct String16S {
  char* mpBegin;         // +0x00
  char* mpEnd;           // +0x04
  char* mpCapacity;      // +0x08
  unsigned int mAlloc;   // +0x0c
};
// A 0x14-byte eastl::basic_string<char, fixed_vector_allocator> (used by the helpers below).
struct FixedVectorAllocator {
  unsigned int mOverflowAllocator;  // +0x00
  void* mpPoolBegin;                // +0x04
};
struct FixedStringAlloc {
  FixedVectorAllocator mAllocator;
};
struct FixedString8 {
  char* mpBegin;          // +0x00
  char* mpEnd;            // +0x04
  char* mpCapacity;       // +0x08
  FixedVectorAllocator mAllocator;  // +0x0c
  FixedString8(const FixedString8& x);   // 0x00618af0
  void assign(const char* b, const char* e);  // 0x0060a2c0
  void shrink_capacity(unsigned int n);       // 0x006174e0
  void swap(FixedString8& x);                 // 0x0061bc50
  void set_capacity(unsigned int n);          // 0x0061c280
};

// @ 0x0061bc50  eastl::basic_string<char, fixed_vector_allocator>::swap
void FixedString8::swap(FixedString8& x) {
  if ((char*)this + 0xc == (char*)&x + 0xc) {
    char* p0 = mpBegin;
    mpBegin = x.mpBegin;
    x.mpBegin = p0;
    char* p1 = mpEnd;
    mpEnd = x.mpEnd;
    x.mpEnd = p1;
    char* p2 = mpCapacity;
    mpCapacity = x.mpCapacity;
    x.mpCapacity = p2;
    return;
  }
  FixedString8 tmp(*this);
  if (&x != this) assign(x.mpBegin, x.mpEnd);
  if (&tmp != &x) x.assign(tmp.mpBegin, tmp.mpEnd);
  if ((tmp.mpCapacity - tmp.mpBegin) > 1 && tmp.mpBegin &&
      tmp.mpBegin != (char*)tmp.mAllocator.mpPoolBegin)
    EASTL_allocator_deallocate(tmp.mpBegin);
}

// @ 0x0061c280  eastl::basic_string<char, fixed_vector_allocator>::set_capacity
void FixedString8::set_capacity(unsigned int n) {
  if (n != 0xffffffffu && (unsigned int)(mpEnd - mpBegin) < n) {
    char* dst = (char*)EASTL_allocator_allocate(
        n, "Editor", 0, 0,
        "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include"
        "\\EASTL/allocator.h",
        0xd1);
    unsigned int size = (unsigned int)(mpEnd - mpBegin);
    memcpy(dst, mpBegin, size);
    dst[size] = 0;
    if ((mpCapacity - mpBegin) > 1 && mpBegin && mpBegin != (char*)mAllocator.mpPoolBegin)
      EASTL_allocator_deallocate(mpBegin);
    mpBegin = dst;
    mpEnd = dst + size;
    mpCapacity = dst + n;
    return;
  }
  if (n < (unsigned int)(mpEnd - mpBegin)) shrink_capacity(n);
  FixedString8 tmp(*this);
  swap(tmp);
}

// =============================================================================================
// EASTL sort internals: comparator over unsigned indices into 0x118-byte timed records.
struct TimedRec {
  char pad[0x30];
  long long mTime;  // +0x30
  char pad2[0x118 - 0x38];
};
struct TimedTable {
  char pad[0x60];
  TimedRec* mpTable;  // +0x60
};
struct TimeGreater {
  TimedTable* mpOwner;
  bool operator()(unsigned int a, unsigned int b) const {
    return mpOwner->mpTable[a].mTime > mpOwner->mpTable[b].mTime;
  }
};
const unsigned int& median(const unsigned int& a, const unsigned int& b, const unsigned int& c,
                           TimeGreater compare);  // 0x006168a0
unsigned int* get_partition(unsigned int* first, unsigned int* last, unsigned int pivot,
                            TimeGreater compare);  // 0x006189e0
void insertion_sort(unsigned int* first, unsigned int* last, TimeGreater compare);  // 0x00619530

// @ 0x0061bbc0
void quick_sort_impl(unsigned int* first, unsigned int* last, int kRecursionCount,
                     TimeGreater compare) {
  while (((last - first) > 28) && (kRecursionCount > 0)) {
    unsigned int* const position = get_partition(
        first, last, median(*first, *(first + (last - first) / 2), *(last - 1), compare), compare);
    quick_sort_impl(position, last, --kRecursionCount, compare);
    last = position;
  }
  if (kRecursionCount == 0) insertion_sort(first, last, compare);
}

// =============================================================================================
// EASTL container primitives.
struct Rec70 {  // 0x70-byte record with out-of-line ctor/dtor
  unsigned int m0, m4, m8;
  unsigned char pad[0x70 - 12];
  Rec70();   // 0x00549500
  ~Rec70();  // 0x00547840
};
struct Vec70S {  // 0x14-byte eastl::vector<T, sp_allocator> header
  void* mpBegin;     // +0x00
  void* mpEnd;       // +0x04
  void* mpCapacity;  // +0x08
  unsigned int mStateC;
  unsigned int mState10;
};
void UninitFill70(unsigned int* pn, const void* a, const void* b, void* dst,
                  unsigned int n);  // 0x006195d0
long ByteVectorAllocate(unsigned int n, const void* src, unsigned int nbytes);  // 0x005968b0
void VectorCopyBytes(void* dst, const void* src, unsigned int nbytes);          // 0x011e0744

// @ 0x0061c1c0  DoAllocate + uninitialized_fill of 0x70-byte records
void* AllocateAndFill70(unsigned int n, const void* a, const void* b) {
  void* result = 0;
  if (n != 0)
    result = EASTL_allocator_allocate(n * 0x70, "Editor", 0, 0,
                                      "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\"
                                      "Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                                      0xd1);
  UninitFill70(&n, a, b, result, n);
  return result;
}

// @ 0x0061c070  eastl::vector<T, fixed_vector_allocator>::operator=
void* VectorAssign(void* self, void* x) {
  if (x == self) return self;
  char** s = (char**)self;
  char** o = (char**)x;
  unsigned int n = (unsigned int)(o[1] - o[0]) >> 3;
  if ((unsigned int)(s[2] - s[0]) >> 3 < n) {
    char* p = (char*)ByteVectorAllocate(n, o[0], (unsigned int)(o[1] - o[0]));
    if (s[0] && *((int*)s[0] - 1) != 0) EASTL_allocator_deallocate(s[0]);
    s[0] = p;
    s[2] = p + n * 8;
    s[1] = p + n * 8;
    return self;
  }
  unsigned int have = (unsigned int)(s[1] - s[0]) >> 3;
  if (have < n) {
    VectorCopyBytes(s[0], o[0], have * 8);
    char* src = o[0] + ((char*)s[1] - (char*)s[0]);
    VectorCopyBytes(s[1], src, (unsigned int)(o[1] - src));
    s[1] = s[0] + n * 8;
    return self;
  }
  VectorCopyBytes(s[0], o[0], (unsigned int)(o[1] - o[0]));
  s[1] = s[0] + n * 8;
  return self;
}

// =============================================================================================
// Message / HTTP plumbing.
namespace EA {
namespace Messaging {
union Data {
  unsigned int mUint32;
  unsigned long long mUint64;
};
class IMessageRC {
 public:
  virtual void Destroy();  // vtable slot 0 (dtor in retail)
  virtual int AddRef();    // +0x04
  virtual int Release();   // +0x08
};
class BehaviorMessage : public IMessageRC {
 public:
  BehaviorMessage() { _InterlockedExchange(&mRefCount, 0); mID = 0; }
  long mRefCount;    // +0x04
  Data mData[5];     // +0x08
  unsigned int mID;  // +0x30
  unsigned int mPad34;
};
class MessageBasicRC5 : public BehaviorMessage {
 public:
  MessageBasicRC5() : mResult(0) {}
  ~MessageBasicRC5();  // 0x00421cf0
  virtual int AddRef();
  unsigned int mResult;  // +0x38
  unsigned int mPad3c;
};
}  // namespace Messaging

namespace Internet {
class HttpRequestBody {
 public:
  virtual ~HttpRequestBody();
  virtual int AddRef();
  virtual int Release();
  virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6();
  virtual void v7(); virtual void v8(); virtual void v9(); virtual void v10();
  virtual void v11(); virtual void v12(); virtual void v13(); virtual void v14();
  virtual void v15(); virtual void v16(); virtual void v17(); virtual void v18();
  virtual void v19(); virtual void v20(); virtual void v21();
  virtual bool AddField(const char* value);                       // +0x58
  virtual bool AddFormField(const char* a, const char* b, void* c);  // +0x5c
};
class HTTPMultipartRelatedPostBodyStream : public HttpRequestBody {
 public:
  HTTPMultipartRelatedPostBodyStream();  // 0x0060c510
};
class HTTPHeaders {
 public:
  void AddHeaderEntry(const char* name, void* value);  // 0x00944cb0
  void AddHeaderEntry(const char* name, const char* value);
};
class HTTPRequest {
 public:
  virtual ~HTTPRequest();
  long mRefCount;              // +0x04
  char pad[0x2f4 - 8];
  HTTPHeaders mHeaders;        // +0x2f4
  unsigned int mCallbackVtbl;  // +0xd94
  static bool CreateHTTPPostRequest(const char* url, HttpRequestBody* body, void* async, void* out);
  static bool CreateHTTPGetRequest(const char* url, void* async, void* out);
};
}  // namespace Internet
}  // namespace EA

struct AsyncRequest {
  virtual ~AsyncRequest();
  int mRefCount;
  AsyncRequest(int, int, const char* name);  // 0x0093c270
  void SetPriority(int mode, float f);       // 0x0093bb40
};
struct RequestAutoPtr {
  EA::Internet::HTTPRequest* mpObject;
  RequestAutoPtr() : mpObject(0) {}
  ~RequestAutoPtr();                        // 0x0060d210
  EA::Internet::HTTPRequest** operator&();  // 0x0060d240
};
struct ResourceObject {
  virtual void v0();
  virtual void v1();
  virtual void v2();
  virtual void v3();
  virtual void v4();
  virtual void v5();
  virtual int GetSize();  // +0x18
};
struct ResourceDatabase {
  virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
  virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
  virtual void v8(); virtual void v9(); virtual void v10(); virtual void v11();
  virtual void v12();
  virtual bool GetResource(void* key, void** out, int, int, int, int);  // +0x34
};

void GetVideoServiceURL(void* key, void* out);     // 0x00621460
void* GetSaveArea(void* id);                       // 0x0067de30
void AddRequestHeader(int id, const char* value);  // 0x00944660

// A downloaded-content handle; the interesting object hangs off +0xf3c.
struct IXfer {
  virtual void v0();
  virtual int AddRef();                 // +0x04
  virtual int Release();                // +0x08
  virtual void v3();
  virtual void v4();
  virtual int GetStatus();              // +0x14
  virtual bool IsComplete();            // +0x18
  virtual char* GetData();              // +0x1c
  virtual void v8();
  virtual void v9();
  virtual void Seek(int, int);          // +0x28
  virtual void Read(void* dst, int n);  // +0x30
};
struct DownloadObject {
  char pad[0xf3c];
  IXfer* mpXfer;  // +0xf3c
};

// ---- the 0xa8-byte content-validation transaction (ctor / dtor) ------------------------------
class cContentValidationTransaction {
 public:
  unsigned int* mVtbl;   // +0x00
  unsigned int mPad4;    // +0x04
  void* mp8;             // +0x08
  void* mpC;             // +0x0c
  void* mp10;            // +0x10
  Vec70S mVec14;         // +0x14
  Vec70S mVec28;         // +0x28
  Vec70S mVec3c;         // +0x3c
  String16S mStr50;      // +0x50
  unsigned int mPad60[6];// +0x60
  String8S mStr78;       // +0x78
  String8S mStr88;       // +0x88
  String8S mStr98;       // +0x98

  cContentValidationTransaction(const char* a, const char* b, int c, void* d, void* e, void* f);
  void Destroy();  // 0x0061bf50
};

// @ 0x0061be80
cContentValidationTransaction::cContentValidationTransaction(const char* a, const char* b, int c,
                                                             void* d, void* e, void* f) {
  mp8 = d;
  mpC = e;
  mVtbl = (unsigned int*)0x13fc854;
  mp10 = f;
  mPad4 = 0;
  mVec14.mpBegin = 0;
  mVec14.mpEnd = 0;
  mVec14.mpCapacity = 0;
  mVec28.mpBegin = 0;
  mVec28.mpEnd = 0;
  mVec28.mpCapacity = 0;
  mVec3c.mpBegin = 0;
  mVec3c.mpEnd = 0;
  mVec3c.mpCapacity = 0;
  mStr50.mpBegin = gEmptyString;
  mStr50.mpEnd = gEmptyString;
  mStr50.mpCapacity = gEmptyString + 2;
  mStr78.mpBegin = 0;
  mStr78.mpEnd = 0;
  mStr78.mpCapacity = 0;
  mStr78.range_init(a);
  mStr88.mpBegin = 0;
  mStr88.mpEnd = 0;
  mStr88.mpCapacity = 0;
  mStr88.range_init(b);
  mStr98.mpBegin = gEmptyString;
  mStr98.mpEnd = gEmptyString;
  mStr98.mpCapacity = gEmptyString + 1;
  if (c != 0) mStr98.sprintf((const char*)0x13fc850, c);
}

// @ 0x0061bf50
void cContentValidationTransaction::Destroy() {
  *(unsigned int* volatile*)this = (unsigned int*)0x13fc854;
  _ReadWriteBarrier();
  if ((mStr98.mpCapacity - mStr98.mpBegin) > 1 && mStr98.mpBegin)
    EASTL_allocator_deallocate(mStr98.mpBegin);
  if ((mStr88.mpCapacity - mStr88.mpBegin) > 1 && mStr88.mpBegin)
    EASTL_allocator_deallocate(mStr88.mpBegin);
  if ((mStr78.mpCapacity - mStr78.mpBegin) > 1 && mStr78.mpBegin)
    EASTL_allocator_deallocate(mStr78.mpBegin);
  if ((((int)(mStr50.mpCapacity - mStr50.mpBegin) & ~1) > 2) && mStr50.mpBegin)
    EASTL_allocator_deallocate(mStr50.mpBegin);
  char* p;
  char* e;
  e = (char*)mVec3c.mpEnd;
  for (p = (char*)mVec3c.mpBegin; p < e; p += 0x70) ((Rec70*)p)->~Rec70();
  if (mVec3c.mpBegin && *((int*)mVec3c.mpBegin - 1) != 0) EASTL_allocator_deallocate(mVec3c.mpBegin);
  e = (char*)mVec28.mpEnd;
  for (p = (char*)mVec28.mpBegin; p < e; p += 0x70) ((Rec70*)p)->~Rec70();
  if (mVec28.mpBegin && *((int*)mVec28.mpBegin - 1) != 0) EASTL_allocator_deallocate(mVec28.mpBegin);
  e = (char*)mVec14.mpEnd;
  for (p = (char*)mVec14.mpBegin; p < e; p += 0x70) ((Rec70*)p)->~Rec70();
  if (mVec14.mpBegin && *((int*)mVec14.mpBegin - 1) != 0) EASTL_allocator_deallocate(mVec14.mpBegin);
  mVtbl = (unsigned int*)0x13ec458;
}

// ---- the YouTube authentication transaction -------------------------------------------------
class cYouTubeAuthenticationTransaction {
 public:
  virtual ~cYouTubeAuthenticationTransaction();
  char pad4[0x34];
  volatile long mCheckRegistration;  // +0x38 (bool in retail)
  char pad3c[4];
  char HandleResult(int result, DownloadObject* pDownload);  // 0x0061b3b0
};
typedef EA::Messaging::MessageBasicRC5 YoutubeMessage;

// @ 0x0061b3b0
char cYouTubeAuthenticationTransaction::HandleResult(int result, DownloadObject* pDownload) {
  char szTmp[0x64];
  char szUser[0x64];
  String8S url;
  bool bAuth = false;
  unsigned int payload = 0;

  switch (result) {
    case 0: {
      IXfer* pX = pDownload->mpXfer;
      char* pData = pX->GetData();
      pX->Seek(0, 0);
      String8S s;
      s.range_init(pData);
      pX->Read(s.mpBegin, (int)(s.mpEnd - s.mpBegin));
      sscanf(s.mpBegin, "Auth=%s\nYouTubeUser=%s", szTmp, szUser);
      bAuth = true;
      payload = (unsigned int)this;
      break;
    }
    case 5:
    case 6:
    case 9:
      memcpy(szTmp, (char*)pDownload + 0x440, 0x64);
      url.sprintf("%s", szTmp);
      payload = *(unsigned int*)((char*)pDownload + 0x43c);
      break;
    default:
      if (pDownload == 0) {
        url.assign("", "");
        payload = 0;
      } else {
        memcpy(szTmp, (char*)pDownload + 0x440, 0x64);
        url.sprintf("%s", szTmp);
        payload = *(unsigned int*)((char*)pDownload + 0x43c);
      }
      break;
  }

  YoutubeMessage* pMsg = new ("Pollinator", 0, 0, 0, 0) YoutubeMessage();
  pMsg->AddRef();
  pMsg->mID = 0x55e5212;
  if (!bAuth) {
    pMsg->mData[0].mUint32 = 0;
    pMsg->mData[2].mUint32 = payload;
    SetMessageString8(pMsg, 3, url.mpBegin);
  } else {
    pMsg->mData[0].mUint32 = 1;
    SetMessageString8(pMsg, 2, szTmp);
    SetMessageString8(pMsg, 3, szUser);
  }
  pMsg->mData[1].mUint32 = (mCheckRegistration != 0);
  SP::MessageServer()->PostMSG(pMsg->mID, pMsg, 0);
  pMsg->Release();
  if (pDownload != 0 && pDownload->mpXfer != 0) {
    IXfer* pX = pDownload->mpXfer;
    pDownload->mpXfer = 0;
    pX->Release();
  }
  return bAuth;
}

// ---- the YouTube video-upload transaction ---------------------------------------------------
class cYouTubeVideoUploadTransaction {
 public:
  virtual ~cYouTubeVideoUploadTransaction();
  string8 mUsername;             // +0x08
  string8 mClientID;             // +0x18
  string8 mAuthenticationToken;  // +0x28
  string8 mDeveloperKey;         // +0x38
  string8 mVideoFilename;        // +0x48
  unsigned int mVideoKey[3];     // +0x58
  string8 mXMLRequest;           // +0x64
  bool ConstructRequest(void** ppRequest);  // 0x0061b620
};

// @ 0x0061b620
bool cYouTubeVideoUploadTransaction::ConstructRequest(void** ppRequest) {
  EA::Internet::HTTPMultipartRelatedPostBodyStream* pBody =
      new ("Pollinator", 0, 0, 0, 0) EA::Internet::HTTPMultipartRelatedPostBodyStream();
  if (pBody == 0) return false;
  pBody->AddRef();
  AsyncRequest* pAsync = new ("Pollinator", 0, 0, 0, 0) AsyncRequest(0, 0, "UTF/MemoryStream");
  pAsync->SetPriority(1, 1.0f);
  if (!pBody->AddField(mXMLRequest.mpBegin)) {
    pBody->Release();
    return false;
  }
  ResourceDatabase* pDb = (ResourceDatabase*)GetSaveArea((void*)0x11ac197);
  ResourceObject* pRes = 0;
  if (pDb == 0 || !pDb->GetResource(&mVideoKey, (void**)&pRes, 1, 6, 1, 0)) {
    pBody->Release();
    return false;
  }
  int nSize = pRes->GetSize();
  if (!pBody->AddFormField("video/avi", "binary", (void*)nSize)) {
    if (pRes) pRes->v1();
    pBody->Release();
    return false;
  }
  String8S url;
  url.sprintf("%s", (void*)0x55e8f9c);
  url.append_sprintf("/%s/uploads", mUsername.mpBegin);
  RequestAutoPtr req;
  if (!EA::Internet::HTTPRequest::CreateHTTPPostRequest(url.mpBegin, pBody, pAsync, &req)) {
    if (pRes) pRes->v1();
    pBody->Release();
    return false;
  }
  _InterlockedExchangeAdd(&req.mpObject->mRefCount, 1);
  AddRequestHeader(0x13fc238, mClientID.mpBegin);
  {
    String8S hdr;
    hdr.sprintf("%s", "GoogleLogin auth=");
    hdr.append_sprintf("%s", mAuthenticationToken.mpBegin);
    req.mpObject->mHeaders.AddHeaderEntry("Authorization", (void*)hdr.mpBegin);
    hdr.clear();
    hdr.sprintf("%s", (void*)0x13fc1f8);
    hdr.append_sprintf("%s", mDeveloperKey.mpBegin);
    req.mpObject->mHeaders.AddHeaderEntry("X-GData-Key", (void*)hdr.mpBegin);
  }
  req.mpObject->mHeaders.AddHeaderEntry((const char*)0x13fc1f0, (void*)mVideoFilename.mpBegin);
  req.mpObject->mCallbackVtbl = 0x15206f0;
  *ppRequest = req.mpObject;
  if (pRes) pRes->v1();
  pBody->Release();
  return true;
}

// ---- Pollen request helper (posts a login/pollen request message) ---------------------------
// @ 0x0061b9a0
char PollenRequestHelper(unsigned int which, DownloadObject* pDownload) {
  char szTmp[0x64];
  String8S url;
  bool bFound = false;
  unsigned int payload = 0;

  switch (which) {
    case 0: {
      IXfer* pOuter = pDownload->mpXfer ? (IXfer*)((char*)pDownload->mpXfer - 8) : 0;
      IXfer* pX = (IXfer*)((char*)pOuter + 8);
      int nStatus = pX->GetStatus();
      bool bDone = pX->IsComplete();
      if (nStatus == 0 && bDone) {
        payload = (unsigned int)Fun_00614e50("i");
        bFound = true;
      }
      break;
    }
    case 5:
    case 6:
    case 9:
      memcpy(szTmp, (char*)pDownload + 0x440, 0x64);
      url.sprintf("%s", szTmp);
      payload = *(unsigned int*)((char*)pDownload + 0x43c);
      break;
    default:
      if (pDownload == 0) {
        url.assign("", "");
        payload = 0;
      } else {
        memcpy(szTmp, (char*)pDownload + 0x440, 0x64);
        url.sprintf("%s", szTmp);
        payload = *(unsigned int*)((char*)pDownload + 0x43c);
      }
      break;
  }

  YoutubeMessage* pMsg = new ("Pollinator", 0, 0, 0, 0) YoutubeMessage();
  pMsg->AddRef();
  pMsg->mID = 0x55e8be4;
  if (bFound) {
    pMsg->mData[0].mUint32 = 1;
    SetMessageString8(pMsg, 1, (const char*)payload);
  } else {
    pMsg->mData[0].mUint32 = 0;
    pMsg->mData[1].mUint32 = payload;
    SetMessageString8(pMsg, 2, url.mpBegin);
  }
  SP::MessageServer()->PostMSG(pMsg->mID, pMsg, 0);
  pMsg->Release();
  if (pDownload != 0 && pDownload->mpXfer != 0) {
    IXfer* pX = pDownload->mpXfer;
    pDownload->mpXfer = 0;
    pX->Release();
  }
  return bFound;
}

// ---- property-list / PNG writer -------------------------------------------------------------
void* Fun_00c463d0(int a, int b, int c, int d);   // 0x00c463d0
void Fun_0060d210(void* p);                       // 0x0060d210
void* Fun_0060d240(void* p);                      // 0x0060d240
namespace eastl {
template <typename It, typename T>
It lower_bound(It first, It last, const T& value, unsigned char comp);  // 0x00549dc0
unsigned int* lower_bound(unsigned int* first, unsigned int* last, const unsigned int& value,
                          unsigned char comp);  // 0x00549dc0
}

class cPropertyListWriter {
 public:
  char pad4[4];
  void* mp8;            // +0x08
  unsigned int mIndex;  // +0x0c
  unsigned int mKey;    // +0x10
  unsigned int mVal14;  // +0x14
  unsigned int mVal18;  // +0x18
  unsigned int mVal1c;  // +0x1c
  void* mp20;           // +0x20
  bool WritePropertyListAndPNG();  // 0x0061bcf0
};

// @ 0x0061bcf0
bool cPropertyListWriter::WritePropertyListAndPNG() {
  char* pOwner = (char*)mp8;
  if (pOwner == 0) return false;
  if (mIndex > (unsigned int)((*(int*)(pOwner + 100) - *(int*)(pOwner + 0x60)) / 0x118))
    return false;
  char* pRec = (char*)(*(int*)(pOwner + 0x60) + mIndex * 0x118);
  unsigned int* pBegin = *(unsigned int**)(pRec + 0x90);
  unsigned int* pFound =
      (unsigned int*)eastl::lower_bound(*(unsigned int**)(pRec + 0x8c), pBegin, &mKey,
                                        *(unsigned char*)(pRec + 0xa0));
  unsigned int* pFirst = pBegin;
  if (pFound != pBegin && *pFound <= mKey && pFound != pFound + 5) pFirst = pFound;
  if (pFirst != *(unsigned int**)(pRec + 0x90) && mKey < 0x100 && pFirst[1] != pFirst[2]) {
    unsigned int local_c = mVal14;
    unsigned int local_4 = mVal1c ^ ((mKey ^ mVal1c) & 0xff);
    unsigned int local_8 = 0x2f7d0004;
    (void)local_8;
    ResourceDatabase* pDb = (ResourceDatabase*)GetSaveArea((void*)0x11ac19d);
    if (pDb != 0) {
      void* pArg = Fun_00c463d0(2, 2, 0, 0);
      if (pDb->GetResource(&local_c, &pArg, local_4, 0, 0, 0)) {
        return true;
      }
    }
  }
  return false;
}

}  // namespace Pollen
}  // namespace SP
