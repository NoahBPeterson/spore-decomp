// Slice s00619150: SP::Pollen feed/upload transaction constructors and destructors plus
// three EASTL helpers (partial_sort over unsigned indices keyed by a 64-bit timestamp, and
// two element copy loops for the 0x70-byte SP::Feed::FeedDescription records).
// Flags: /O2 /MD /Gy /TP (no /EHsc).
#include "types.h"
#include <intrin.h>

inline void* operator new(unsigned int, void* p) { return p; }

// ---------------------------------------------------------------------------------------------
// EASTL declarations (callees/globals are relocation-masked; only the convention matters)
// ---------------------------------------------------------------------------------------------
extern "C" void* EASTL_allocator_allocate(unsigned int n, const char* name, int flags, unsigned debugFlags,
                                          const char* file, int line);
extern "C" void EASTL_allocator_deallocate(void* p);

namespace eastl {
struct allocator {
  allocator() {}
};
template <typename T, typename A = allocator>
struct basic_string {
  T* mpBegin;
  T* mpEnd;
  T* mpCapacity;
  A mAllocator;
  basic_string() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
  basic_string(const T* p) : mpBegin(0), mpEnd(0), mpCapacity(0) { RangeInit(p); }
  ~basic_string() {
    if ((mpCapacity - mpBegin) > 1) {
      if (mpBegin) EASTL_allocator_deallocate(mpBegin);
    }
  }
  void RangeInit(const T* p);  // 0x0057cc10
};
}  // namespace eastl
typedef eastl::basic_string<char> string8;

namespace EA {
template <typename T>
class RefCountVTemplate {
 public:
  RefCountVTemplate() : mRefCount(0) {}
  virtual ~RefCountVTemplate() {}
  virtual int AddRef();
  virtual int Release();
  T mRefCount;
};
}  // namespace EA

namespace SP {
namespace Pollen {
class cITransaction : public EA::RefCountVTemplate<int> {
 public:
  virtual ~cITransaction() {}
};
struct Key {
  uint32_t a, b, c;
};

extern void* gFree1;  // 0x015f53d4
extern void* gFree2;  // 0x015f5614

class cDeleteMyFeedTransaction : public cITransaction {
 public:
  string8 mURI;  // +0x8
  cDeleteMyFeedTransaction(const char* uri);
  static void operator delete(void* p) {
    *(void**)p = gFree1;
    gFree1 = p;
  }
  virtual ~cDeleteMyFeedTransaction() {}
};
class cFeedUnsubscribeTransaction : public cITransaction {
 public:
  string8 mURI;  // +0x8
  cFeedUnsubscribeTransaction(const char* uri);
  static void operator delete(void* p) {
    *(void**)p = gFree2;
    gFree2 = p;
  }
  virtual ~cFeedUnsubscribeTransaction() {}
};
class cSnapshotUploadTransaction : public cITransaction {
 public:
  Key mKey;                          // +0x8
  string8 mMyEmailAddress;           // +0x14
  string8 mDestinationEmailAddress;  // +0x24
  string8 mMessageText;              // +0x34
  string8 mLocale;                   // +0x44
  virtual ~cSnapshotUploadTransaction() {}
  cSnapshotUploadTransaction(const Key& key, const char* myEmail, const char* destEmail,
                             const char* message, const char* locale);
};
class cYouTubeAuthenticationTransaction : public cITransaction {
 public:
  string8 mUsername;        // +0x8
  string8 mPassword;        // +0x18
  string8 mSource;          // +0x28
  bool mCheckRegistration;  // +0x38
  virtual ~cYouTubeAuthenticationTransaction() {}
  cYouTubeAuthenticationTransaction(const char* username, const char* password, const char* source,
                                    bool check);
};
class cYouTubeVideoUploadTransaction : public cITransaction {
 public:
  string8 mUsername;             // +0x8
  string8 mClienID;              // +0x18
  string8 mAuthenticationToken;  // +0x28
  string8 mDeveloperKey;         // +0x38
  string8 mVideoFilename;        // +0x48
  Key mVideoKey;                 // +0x58
  string8 mXMLRequest;           // +0x64
  virtual ~cYouTubeVideoUploadTransaction() {}
  cYouTubeVideoUploadTransaction(const char* username, const char* clientID, const char* authToken,
                                 const char* devKey, const char* videoFilename, Key videoKey,
                                 const char* xmlRequest);
};
class cYouTubeVideoURLTransaction : public cITransaction {
 public:
  string8 mMyEmailAddress;           // +0x8
  string8 mDestinationEmailAddress;  // +0x18
  string8 mMessageText;              // +0x28
  string8 mLocale;                   // +0x38
  virtual ~cYouTubeVideoURLTransaction() {}
  cYouTubeVideoURLTransaction(const char* myEmail, const char* destEmail, const char* message,
                              const char* locale);
};

// @ 0x00619150
cDeleteMyFeedTransaction::cDeleteMyFeedTransaction(const char* uri) : mURI(uri) {}

// @ 0x006191d0
cFeedUnsubscribeTransaction::cFeedUnsubscribeTransaction(const char* uri) : mURI(uri) {}

// @ 0x00619250
cSnapshotUploadTransaction::cSnapshotUploadTransaction(const Key& key, const char* myEmail,
                                                       const char* destEmail, const char* message,
                                                       const char* locale)
    : mKey(key),
      mMyEmailAddress(myEmail),
      mDestinationEmailAddress(destEmail),
      mMessageText(message),
      mLocale(locale) {}

// @ 0x00619300
cYouTubeAuthenticationTransaction::cYouTubeAuthenticationTransaction(const char* username,
                                                                     const char* password,
                                                                     const char* source,
                                                                     bool check)
    : mUsername(username), mPassword(password), mSource(source), mCheckRegistration(check) {}

// @ 0x00619390
cYouTubeVideoUploadTransaction::cYouTubeVideoUploadTransaction(const char* username,
                                                               const char* clientID,
                                                               const char* authToken,
                                                               const char* devKey,
                                                               const char* videoFilename,
                                                               Key videoKey, const char* xmlRequest)
    : mUsername(username),
      mClienID(clientID),
      mAuthenticationToken(authToken),
      mDeveloperKey(devKey),
      mVideoFilename(videoFilename),
      mVideoKey(videoKey),
      mXMLRequest(xmlRequest) {}

// @ 0x00619470
cYouTubeVideoURLTransaction::cYouTubeVideoURLTransaction(const char* myEmail, const char* destEmail,
                                                         const char* message, const char* locale)
    : mMyEmailAddress(myEmail),
      mDestinationEmailAddress(destEmail),
      mMessageText(message),
      mLocale(locale) {}
}  // namespace Pollen
}  // namespace SP

// ---------------------------------------------------------------------------------------------
// 0x70-byte SP::Feed::FeedDescription record (copy ctor / assignment are out of line)
// ---------------------------------------------------------------------------------------------
struct FeedDescription {
  uint32_t mData[0x70 / 4];
  FeedDescription();
  FeedDescription(const FeedDescription& x);
  FeedDescription& operator=(const FeedDescription& x);
};

// ---------------------------------------------------------------------------------------------
// EASTL sort helpers (indices into 0x118-byte timestamped records, descending by 64-bit time)
// ---------------------------------------------------------------------------------------------
struct sTimedRec {
  char pad[0x30];
  int64_t mTime;  // +0x30
  char pad2[0x118 - 0x38];
};
struct sTimedOwner {
  char pad[0x60];
  sTimedRec* mpTable;
};
struct TimeGreater {
  sTimedOwner* mpOwner;
  bool operator()(unsigned int a, unsigned int b) const {
    return mpOwner->mpTable[a].mTime > mpOwner->mpTable[b].mTime;
  }
};
void AdjustHeap(unsigned int* first, int topPosition, int heapSize, int position, unsigned int value,
                TimeGreater cmp);  // 0x00617530
void MakeHeap(unsigned int* first, unsigned int* last, TimeGreater cmp);   // 0x00618a60
void SortHeap(unsigned int* first, unsigned int* last, TimeGreater cmp);  // 0x00618aa0

// @ 0x00619530
void partial_sort(unsigned int* first, unsigned int* middle, unsigned int* last, TimeGreater compare) {
  MakeHeap(first, middle, compare);
  for (unsigned int* i = middle; i < last; ++i) {
    if (compare(*i, *first)) {
      unsigned int temp = *i;
      *i = *first;
      AdjustHeap(first, 0, (int)(middle - first), 0, temp, compare);
    }
  }
  SortHeap(first, middle, compare);
}

// @ 0x006195d0
FeedDescription** uninitialized_copy_rev(FeedDescription** ppResult, FeedDescription* last,
                                         FeedDescription* first, FeedDescription* dest) {
  *ppResult = dest;
  while (last != first) {
    --last;
    if (*ppResult) new (*ppResult) FeedDescription(*last);
    ++*ppResult;
  }
  return ppResult;
}

// @ 0x00619650
FeedDescription* copy_rev(FeedDescription* first, FeedDescription* last, FeedDescription* dest) {
  if (first == last) return dest;
  do {
    --first;
    *dest = *first;
    ++dest;
  } while (first != last);
  return dest;
}
