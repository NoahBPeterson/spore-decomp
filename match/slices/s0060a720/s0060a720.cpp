// Pollen HTTP cookie handler (SP::Pollen::CookieHandler) and the editor DB-check dialog (UI::DBCheck).
// Flags: /O2 /MD /Gy /TP /arch:SSE /GS-  (no /EHsc)
#include "s0060a720.h"

extern "C" long __cdecl _InterlockedExchange(long volatile*, long);

struct ListNodeBase {
  ListNodeBase* mpNext;
  ListNodeBase* mpPrev;
};


namespace EA {
namespace Thread {
struct AutoFutex {
  void* mpFutex;
  AutoFutex(void* p) : mpFutex(p) { EnterCriticalSection(p); }
  ~AutoFutex() { LeaveCriticalSection(mpFutex); }
};
}  // namespace Thread
namespace Internet {
struct HTTPHeaders {
  void RemoveHeaderEntry(int fieldID, int index);                        // 0x00944ac0
  bool SetHeaderEntry(int fieldID, const char* pValue);                  // 0x00944db0
  bool GetHeaderEntry(int fieldID, const char** ppValue, int index);     // 0x009420e0
};
}  // namespace Internet
}  // namespace EA

// fixed_string<char, 512> / fixed_vector<cCookie*, 32> as laid out in the request filter's frame.
struct FixedString512 {
  char* mpBegin;
  char* mpEnd;
  char* mpCapacity;
  uint32_t mOverflowAllocator;
  void* mpPoolBegin;
  char mBuffer[512];
  FixedString512& append(const char* pBegin, const char* pEnd);  // 0x0060a150
};
void AppendFormat(FixedString512* pString, const char* pFormat, ...);  // 0x00619510 (sprintf_append)

struct FixedCookieVector {
  SP::Pollen::cCookie** mpBegin;
  SP::Pollen::cCookie** mpEnd;
  SP::Pollen::cCookie** mpCapacity;
  uint32_t mOverflowAllocator;
  void* mpPoolBegin;
  uint32_t pad;
  SP::Pollen::cCookie* mBuffer[32];
  void DoInsertValue(SP::Pollen::cCookie** position, SP::Pollen::cCookie* const& value);  // 0x0060a600
};
char* find_first_of_chars(char* first1, char* last1, const char* first2, const char* last2);  // 0x00609d50

namespace SP {
namespace Pollen {

typedef EA::COM::AutoRefCount<cCookie> CookiePtr;

struct CookieNode : public ListNodeBase {
  CookiePtr mValue;
};
struct CookieIterator {
  CookieNode* mpNode;
  CookieIterator(CookieNode* p) : mpNode(p) {}
  CookieIterator(const CookieIterator& x) : mpNode(x.mpNode) {}
  CookieIterator& operator++() {
    mpNode = (CookieNode*)mpNode->mpNext;
    return *this;
  }
};
struct CookieList {
  ListNodeBase mNode;
  uint32_t mAllocator;
  CookieIterator erase(CookieIterator position);  // 0x0060a5a0
  void DoClear();                                 // 0x0060a270
  void DoInit() {
    mNode.mpNext = &mNode;
    mNode.mpPrev = &mNode;
  }
};

struct HTTPRequest {
  uint32_t pad0[12];
  cURLParts mURL;                        // +0x30
  char pad1[0x2f4 - 0x30 - sizeof(cURLParts)];
  EA::Internet::HTTPHeaders mHeaders;    // +0x2f4
};
struct HTTPResponse {
  uint32_t pad0[2];
  const char* mpURL;                     // +0x8
  char pad1[0x4a4 - 0xc];
  EA::Internet::HTTPHeaders mHeaders;    // +0x4a4
};

class IRequestResponseFilter {
 public:
  IRequestResponseFilter() {}
  virtual ~IRequestResponseFilter() {}
  virtual const char* GetName() = 0;
  virtual bool Filter(HTTPResponse* pResponse) = 0;
  virtual bool Filter(HTTPRequest* pRequest) = 0;
  EA::Thread::AtomicInt<int> mRefCount;  // +0x4
};

class CookieHandler : public IRequestResponseFilter {
 public:
  CookieHandler(unsigned short maxCookies, unsigned int bufferSize);
  virtual ~CookieHandler();
  virtual const char* GetName();
  virtual bool Filter(HTTPRequest* pRequest);
  virtual bool Filter(HTTPResponse* pResponse);

  void Clear();
  cCookie* ParseCookieHeader(const char* pHeader);  // 0x0060a340
  bool ApplyURLDefaults(cCookie* pCookie, const char* pURL);
  void AddCookie(const char* pHeader, const char* pURL);

  char* mCookieParseBuffer;       // +0x8
  unsigned int mBufferSize;       // +0xc
  unsigned short mMaxCookies;     // +0x10
  CookieList mCookies;            // +0x14
  unsigned short mNumCookies;     // +0x20
  char pad24[4];
  EA::Thread::Futex mFutex;       // +0x28
};

// @ 0x0060a100 helper
static __declspec(noinline) bool DomainMatches(const string8& domain, const string8& host) {
  const int offset = (int)(host.mpEnd - host.mpBegin) - (int)(domain.mpEnd - domain.mpBegin);
  if (_stricmp(host.mpBegin + offset, domain.mpBegin) == 0) {
    if (offset == 0 || *domain.mpBegin == '.' || host.mpBegin[offset - 1] == '.') return true;
  }
  return false;
}

static __forceinline bool DomainMatchesInline(const string8& domain, const string8& host) {
  const int offset = (int)(host.mpEnd - host.mpBegin) - (int)(domain.mpEnd - domain.mpBegin);
  if (_stricmp(host.mpBegin + offset, domain.mpBegin) == 0) {
    if (offset == 0 || *domain.mpBegin == '.' || host.mpBegin[offset - 1] == '.') return true;
  }
  return false;
}

static inline unsigned int FindFirst(const string8& s, char c) {
  const unsigned int nLength = (unsigned int)(s.mpEnd - s.mpBegin);
  if (0 < nLength) {
    const char* p = s.mpBegin;
    while (p != s.mpEnd && *p != c) ++p;
    if (p != s.mpEnd) return (unsigned int)(p - s.mpBegin);
  }
  return (unsigned int)-1;
}

// @ 0x0060a720  (fills in the domain/path defaults of a cookie from the request URL and validates them)
bool CookieHandler::ApplyURLDefaults(cCookie* pCookie, const char* pURL) {
  cURLParts url(pURL);
  string8& domain = pCookie->mDomain;
  if (pCookie->mDomainDefaulted) {
    domain = url.GetPart(3);
    const unsigned int nDot = FindFirst(domain, '.');
    const unsigned int nLength = (unsigned int)(domain.mpEnd - domain.mpBegin);
    if (nDot < (unsigned int)-1 && nLength > nDot + 1) {
      const unsigned int nDot2 = domain.find('.', nDot + 1);
      if (nDot2 != (unsigned int)-1 && nDot2 < nLength - 1) domain = domain.substr(nDot, (unsigned int)-1);
    }
  } else {
    string8 host(url.GetPart(3));
    const unsigned int nLength = (unsigned int)(domain.mpEnd - domain.mpBegin);
    unsigned int nDot;
    if (nLength > 1 && (nDot = domain.find('.', 1)) != (unsigned int)-1 && nDot < nLength - 1) {
      if (!DomainMatches(domain, host)) return false;
    } else {
      if (domain.compare(host) != 0) return false;
    }
  }
  if (pCookie->mPathDefaulted) {
    pCookie->mPath = url.GetPart(5);
    pCookie->mPath = pCookie->mPath.substr(0, pCookie->mPath.rfind('/', (unsigned int)-1));
  } else {
    string8 path(url.GetPart(5));
    if (path.find(pCookie->mPath, 0) != 0) return false;
  }
  return true;
}

// @ 0x0060a960
void CookieHandler::Clear() {
  EnterCriticalSection(&mFutex);
  mCookies.DoClear();
  mCookies.DoInit();
  mNumCookies = 0;
  LeaveCriticalSection(&mFutex);
}

// @ 0x0060a990
CookieHandler::CookieHandler(unsigned short maxCookies, unsigned int bufferSize) {
  mBufferSize = bufferSize;
  mMaxCookies = maxCookies;
  mCookies.DoInit();
  mNumCookies = 0;
  InitializeCriticalSection(&mFutex);
  mCookieParseBuffer = (char*)operator new(mBufferSize, "UTFInternet/char8_t", 0, 0, 0, 0);
}

// @ 0x0060a9f0  (scalar deleting destructor)
CookieHandler::~CookieHandler() {
  operator delete(mCookieParseBuffer);
  DeleteCriticalSection(&mFutex);
  mCookies.DoClear();
}

// @ 0x0060ada0
void CookieHandler::AddCookie(const char* pHeader, const char* pURL) {
  struct RefHolder {
    cCookie* mpObject;
  } ref;
  ref.mpObject = ParseCookieHeader(pHeader);
  cCookie* const pNew = ref.mpObject;
  if (pNew) {
    pNew->AddRef();
    if (ApplyURLDefaults(pNew, pURL)) {
      for (CookieIterator it((CookieNode*)mCookies.mNode.mpNext); it.mpNode != (CookieNode*)&mCookies.mNode; ++it) {
        cCookie* pOld = it.mpNode->mValue.mpObject;
        if (string8::comparei(pOld->mName.mpBegin, pOld->mName.mpEnd, pNew->mName.mpBegin, pNew->mName.mpEnd) == 0 &&
            pOld->mDomain.compare(pNew->mDomain) == 0 && pOld->mPath.comparei(pNew->mPath) == 0) {
          if (pNew->mMaxAge == 0) {
            mCookies.erase(it);
            --mNumCookies;
          } else {
            it.mpNode->mValue = *(CookiePtr*)&ref;
          }
          return;
        }
      }
      ListNodeBase* const pFirst = mCookies.mNode.mpNext;
      CookieNode* const pNode = (CookieNode*)EASTL_allocator_allocate(sizeof(CookieNode), "Editor", 0, 0, "EASTL/allocator.h", 0xd1);
      if (&pNode->mValue) {
        pNode->mValue.mpObject = pNew;
        pNew->AddRef();
      }
      pNode->mpNext = pFirst;
      pNode->mpPrev = pFirst->mpPrev;
      pFirst->mpPrev->mpNext = pNode;
      pFirst->mpPrev = pNode;
      ++mNumCookies;
      if (mNumCookies > mMaxCookies) {
        CookieNode* const pLast = (CookieNode*)mCookies.mNode.mpPrev;
        pLast->mpPrev->mpNext = pLast->mpNext;
        pLast->mpNext->mpPrev = pLast->mpPrev;
        pLast->mValue.~CookiePtr();
        EASTL_allocator_deallocate(pLast);
        --mNumCookies;
      }
    }
    pNew->Release();
  }
}


// @ 0x0060afa0
bool CookieHandler::Filter(HTTPResponse* pResponse) {
  EA::Thread::AutoFutex lock(&mFutex);
  const char* pHeader;
  for (int i = 0; pResponse->mHeaders.GetHeaderEntry(0x34, &pHeader, i); ++i) AddCookie(pHeader, pResponse->mpURL);
  for (int i = 0; pResponse->mHeaders.GetHeaderEntry(0x35, &pHeader, i); ++i) AddCookie(pHeader, pResponse->mpURL);
  return true;
}

// @ 0x0060aa40
bool CookieHandler::Filter(HTTPRequest* pRequest) {
  pRequest->mHeaders.RemoveHeaderEntry(0x36, 0);
  string8& host = pRequest->mURL.GetPart(3);
  string8& path = pRequest->mURL.GetPart(5);
  if (host.mpBegin != host.mpEnd && path.mpBegin != path.mpEnd) {
    EA::Thread::AutoFutex lock(&mFutex);
    FixedCookieVector matches;
    matches.mpBegin = matches.mpEnd = matches.mBuffer;
    matches.mpPoolBegin = matches.mBuffer;
    matches.mpCapacity = matches.mBuffer + 32;
    int version = 1;
    for (CookieNode* pNode = (CookieNode*)mCookies.mNode.mpNext; pNode != (CookieNode*)&mCookies.mNode;
         pNode = (CookieNode*)pNode->mpNext) {
      cCookie* const pCookie = pNode->mValue.mpObject;
      if (path.mpBegin != path.mpEnd) {
        char* const pFound = find_first_of_chars(path.mpBegin, path.mpEnd, pCookie->mPath.mpBegin, pCookie->mPath.mpEnd);
        if (pFound != path.mpEnd && (pFound - path.mpBegin) == 0) {
          if (DomainMatchesInline(pCookie->mDomain, host)) {
            if (version > pNode->mValue.mpObject->mVersion) version = pNode->mValue.mpObject->mVersion;
            cCookie* const pValue = pNode->mValue.mpObject;
            if (matches.mpEnd < matches.mpCapacity) {
              cCookie** const pSlot = matches.mpEnd++;
              if (pSlot) *pSlot = pValue;
            } else {
              matches.DoInsertValue(matches.mpEnd, pValue);
            }
          }
        }
      }
    }
    if (matches.mpBegin != matches.mpEnd) {
      FixedString512 header;
      header.mBuffer[0] = 0;
      header.mpBegin = header.mpEnd = header.mBuffer;
      header.mpPoolBegin = header.mBuffer;
      header.mpCapacity = header.mBuffer + 512;
      if (version > 0) AppendFormat(&header, "$Version=%d; ", version);
      for (cCookie** pp = matches.mpBegin; pp != matches.mpEnd; ++pp) {
        const char* const pName = (*pp)->mName.mpBegin;
        const char* const pValue = (*pp)->mValue.mpBegin;
        const char* e = pName;
        while (*e) ++e;
        header.append(pName, e);
        header.append("=", "=" + 1);
        e = pValue;
        while (*e) ++e;
        header.append(pValue, e);
        header.append("; ", "; " + 2);
        if (version > 0) {
          if (!(*pp)->mDomainDefaulted) {
            const char* const pDomain = (*pp)->mDomain.mpBegin;
            header.append("$Domain=", "$Domain=" + 8);
            e = pDomain;
            while (*e) ++e;
            header.append(pDomain, e);
            header.append("; ", "; " + 2);
          }
          if (!(*pp)->mPathDefaulted) {
            const char* const pPath = (*pp)->mPath.mpBegin;
            header.append("$Path=", "$Path=" + 6);
            e = pPath;
            while (*e) ++e;
            header.append(pPath, e);
            header.append("; ", "; " + 2);
          }
        }
      }
      pRequest->mHeaders.SetHeaderEntry(0x36, header.mpBegin);
      if ((header.mpCapacity - header.mpBegin) > 1 && header.mpBegin && header.mpBegin != header.mpPoolBegin)
        EASTL_allocator_deallocate(header.mpBegin);
    }
    if (matches.mpBegin && matches.mpBegin != matches.mpPoolBegin) EASTL_allocator_deallocate(matches.mpBegin);
  }
  return true;
}

}  // namespace Pollen
}  // namespace SP

// ---------------------------------------------------------------------------------------------
// Editor DB-check dialog (UI::cDBCheckDialog / UI::DBCheck) and a second small modal dialog.
// The classes below are stubs with the real field offsets; vtable slots the code calls through are named
// (UTFWin::IWindow slots follow the ModAPI header).

#define PV(n) virtual void pv##n();

namespace UTFWin {
class IWinProc {
 public:
  virtual ~IWinProc() {}
  virtual void pv0() = 0;
  virtual void pv1() = 0;
  virtual void pv2() = 0;
  virtual void pv3() = 0;
};
class IWindow {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual uint32_t GetControlID();  // +0x1c
  PV(8) PV(9) PV(10) PV(11) PV(12) PV(13) PV(14) PV(15)
  PV(16) PV(17) PV(18) PV(19) PV(20) PV(21) PV(22) PV(23)
  PV(24) PV(25) PV(26) PV(27) PV(28) PV(29) PV(30) PV(31)
  virtual void SetCaption(const wchar_t* pText);  // +0x80
  PV(33) PV(34) PV(35) PV(36) PV(37) PV(38) PV(39)
  PV(40) PV(41) PV(42) PV(43) PV(44) PV(45) PV(46) PV(47)
  PV(48) PV(49) PV(50) PV(51) PV(52) PV(53) PV(54) PV(55)
  PV(56) PV(57) PV(58) PV(59) PV(60) PV(61) PV(62) PV(63)
  PV(64)
  virtual void AddWinProc(IWinProc* pWinProc);     // +0x104
  virtual void RemoveWinProc(IWinProc* pWinProc);  // +0x108
};
}  // namespace UTFWin

class IMessageListener {
 public:
  PV(0) PV(1)
};
class IMessageServer {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4)
  virtual void MessageSend(uint32_t messageID, void* pData, void* pListener);  // +0x14
  PV(6) PV(7) PV(8)
  virtual void AddListener(IMessageListener* pListener, uint32_t messageID);   // +0x24
  PV(10)
  virtual void RemoveListener(IMessageListener* pListener, uint32_t messageID, int priority);  // +0x2c
};
class IRefCounted {
 public:
  virtual int AddRef();
  virtual int Release();
  virtual void pv2();
  virtual IRefCounted* Query(uint32_t id);  // +0xc
};
class IObjectTemplateDB {
 public:
  PV(0) PV(1) PV(2) PV(3) PV(4) PV(5) PV(6)
  virtual bool IsBusy();  // +0x1c
  virtual void Reset();   // +0x20
};

namespace SP {
IMessageServer* MessageServer();           // 0x0067dcc0
IObjectTemplateDB* ObjectTemplateDB();     // 0x0067cb40
class cString {
 public:
  cString();                                              // 0x006b5060
  ~cString();                                             // 0x006b5240
  void Load(uint32_t tableID, uint32_t instanceID, int);  // 0x006b54b0
  const wchar_t* GetText();                               // 0x006b55c0
  char pad[0x14];
};
}  // namespace SP

struct ResourceKey {
  uint32_t instanceID;
  uint32_t typeID;
  uint32_t groupID;
};
class cSPUILayout {
 public:
  cSPUILayout();                                                        // 0x00810000
  bool Init(const ResourceKey* pKey, int, uint32_t);                   // 0x008120d0
  UTFWin::IWindow* FindWindowByID(uint32_t controlID, int bRecursive);  // 0x008105b0
  void Shutdown(int);                                                   // 0x00811ad0
  ~cSPUILayout();                                                       // 0x00811fe0
  char pad[0x18];
};
namespace SPUIHelpers {
void BeginModal(UTFWin::IWindow* pWindow, void* pWinProc, int);  // 0x008099a0
void EndModal(UTFWin::IWindow* pWindow, uint32_t result, int);          // 0x00809c50
void AutoSizeWindowForText(UTFWin::IWindow* pWindow, int, int);    // 0x00806e40
}  // namespace SPUIHelpers
void MultiHeapObject_operator_delete(void* p);  // 0x00951330
void operator delete(void* p, const char*);
void* AllocUIObject(unsigned size, unsigned align, const char* pName, void* pHeap);  // 0x009512d0
void* GetUIHeap();                                                                   // 0x009512c0
extern IRefCounted* gpMessageHandle;  // 0x015f3f80

namespace UI {

class cDBCheckDialog;
class AsyncResourceBase {  // Resource::Async, +0x4
 public:
  AsyncResourceBase() { mpResource = 0; }
  virtual ~AsyncResourceBase() {}
  virtual void as0();
  virtual void as1();
  virtual void as2();
  uint32_t mpResource;  // +0x8
};
class cDBCheckDialog : public UTFWin::IWinProc, public AsyncResourceBase {
 public:
  __declspec(noinline) cDBCheckDialog();
  __declspec(noinline) bool Init();
  bool Close(void* pCause);
  virtual void pv0();
  virtual void pv1();
  virtual void pv2();
  virtual void pv3();
  bool mbShown;          // +0xc
  char pad0d[3];
  cSPUILayout mLayout;   // +0x10
};

// @ 0x0060b050
bool cDBCheckDialog::Init() {
  ResourceKey key;
  key.instanceID = 0x4b0ac091;
  key.typeID = 0x510a95b;
  key.groupID = 0x40464100;
  if (mLayout.Init(&key, 1, 0x5b598f7)) {
    UTFWin::IWindow* const pWindow = mLayout.FindWindowByID(0x431e538, 1);
    if (pWindow) {
      pWindow->AddWinProc(this);
      return true;
    }
    mLayout.Shutdown(1);
  }
  SP::MessageServer()->MessageSend(0x8085c4c, 0, 0);
  return false;
}

// @ 0x0060b180
bool cDBCheckDialog::Close(void* pCause) {
  if (mbShown) {
   if (SP::ObjectTemplateDB()) {
    SP::ObjectTemplateDB()->Reset();
    SP::MessageServer()->MessageSend(0x8085c4c, 0, 0);
    UTFWin::IWindow* const pWindow = mLayout.FindWindowByID(0x431e538, 1);
    if (pWindow) {
      SPUIHelpers::EndModal(pWindow, ((UTFWin::IWindow*)pCause)->GetControlID(), 1);
      pWindow->RemoveWinProc(this);
    }
    mLayout.Shutdown(1);
   }
  } else {
    mbShown = true;
  }
  return true;
}

// @ 0x0060b150
cDBCheckDialog::cDBCheckDialog() : mbShown(false) {}

class IEditorDialogA {  // +0x0
 public:
  ~IEditorDialogA() {}
  virtual void a0() = 0;
  virtual void a1() = 0;
  virtual void a2() = 0;
  virtual void a3() = 0;
  virtual bool Init() = 0;      // +0x10
  virtual bool Shutdown() = 0;  // +0x14
  virtual void Show() = 0;      // +0x18
};
class __declspec(novtable) IEditorDialogB {  // +0x4
 public:
  virtual void b0() = 0;
  virtual void OnWinProcEvent(UTFWin::IWindow* pWindow, int) = 0;  // +0x4
  virtual void b2() = 0;
};
class IPaintSystemC {  // +0x8
 public:
  ~IPaintSystemC() {}
  virtual void c0() = 0;
  virtual bool HandleMessage(uint32_t messageID, void* pData) = 0;  // +0x4
};
class cContentValidationSummarizer {  // +0xc
 public:
  cContentValidationSummarizer() : mField(0) {}
  ~cContentValidationSummarizer() {}
  virtual void d0();
  virtual void d1();
  virtual void d2();
  virtual void d3();
  uint32_t mField;  // +0x10
};
template <typename T>
struct DialogRef {
  T* mpObject;
  DialogRef() : mpObject(0) {}
  ~DialogRef() {
    if (mpObject) mpObject->Release();
  }
  void Assign(T* p);  // 0x00b5f950 (EA::AutoRefCount<..>::operator=)
  void reset() {
    T* const p = mpObject;
    if (p) {
      mpObject = 0;
      p->Release();
    }
  }
};
class DBCheck : public IEditorDialogA,
                public IEditorDialogB,
                public IPaintSystemC,
                public cContentValidationSummarizer {
 public:
  DBCheck();
  ~DBCheck();
  virtual bool Init();
  virtual bool Shutdown();
  virtual void Show();
  virtual void OnWinProcEvent(UTFWin::IWindow* pWindow, int);
  virtual bool HandleMessage(uint32_t messageID, void* pData);
  DialogRef<IRefCounted> mpDialog;  // +0x14
};

// @ 0x0060b220
DBCheck::DBCheck() {}

// @ 0x0060b470
DBCheck::~DBCheck() {
  IMessageServer* const pServer = SP::MessageServer();
  if (pServer) pServer->RemoveListener((IMessageListener*)(IPaintSystemC*)this, 0x238de9c, -9999);
  mpDialog.reset();
}

// @ 0x0060b110
bool DBCheck::Init() {
  IMessageServer* const pServer = SP::MessageServer();
  if (pServer) pServer->AddListener((IMessageListener*)(IPaintSystemC*)this, 0x238de9c);
  return true;
}

// @ 0x0060b290
bool DBCheck::Shutdown() {
  IMessageServer* const pServer = SP::MessageServer();
  if (pServer) pServer->RemoveListener((IMessageListener*)(IPaintSystemC*)this, 0x238de9c, -9999);
  mpDialog.reset();
  return true;
}

// @ 0x0060b2e0
void DBCheck::Show() {
  if (SP::ObjectTemplateDB() && !SP::ObjectTemplateDB()->IsBusy()) {
    if (!mpDialog.mpObject) {
      void* const pMem = AllocUIObject(0x28, 4, "UI/cDBCheckDialog", GetUIHeap());
      mpDialog.Assign(pMem ? (IRefCounted*)new (pMem) cDBCheckDialog() : 0);
      ((cDBCheckDialog*)mpDialog.mpObject)->Init();
    }
    IEditorDialogB* const pWinProc = this;
    cDBCheckDialog* const pDialog = (cDBCheckDialog*)mpDialog.mpObject;
    UTFWin::IWindow* const pWindow = pDialog->mLayout.FindWindowByID(0x431e538, 1);
    if (pWindow) SPUIHelpers::BeginModal(pWindow, pWinProc, 1);
  } else if (SP::MessageServer()) {
    SP::MessageServer()->MessageSend(0x8085c4c, 0, 0);
  }
}

// @ 0x0060b390
void DBCheck::OnWinProcEvent(UTFWin::IWindow* pWindow, int) {
  if (pWindow->GetControlID() == 0x431e538) mpDialog.reset();
}

// @ 0x0060b4f0
bool DBCheck::HandleMessage(uint32_t messageID, void* pData) {
  if (messageID == 0x238de9c) {
    Shutdown();
    if (gpMessageHandle) gpMessageHandle->Release();
    gpMessageHandle = 0;
    return true;
  }
  return false;
}

// @ 0x0060b3c0
IRefCounted* GetMessageHandle() {
  if (gpMessageHandle) return gpMessageHandle->Query(0x8085c7e);
  return 0;
}

// @ 0x0060b3e0
void SetMessageHandle(IRefCounted* p) {
  if (p) p->AddRef();
  if (gpMessageHandle) {
    gpMessageHandle->Release();
    gpMessageHandle = 0;
  }
  if (p) {
    gpMessageHandle = p->Query(0x8085c57);
    return;
  }
  gpMessageHandle = 0;
}

// @ 0x0060b440 (scalar deleting destructor)
struct cEditorResourceBase {
  virtual ~cEditorResourceBase();
};


// ---- the "insert disc" prompt dialog (cInsertDiscDialog, see slice s0060b730) ----
class cInsertDiscDialog {
 public:
  bool Init();
  void Show(void* pWinProc, uint32_t captionInstanceID);
  void* v0;
  void* v4;
  void* v8;
  cSPUILayout mLayout;  // +0xc
};

// @ 0x0060b550
bool cInsertDiscDialog::Init() {
  ResourceKey key;
  key.instanceID = 0x5b9f6852;
  key.typeID = 0x510a95b;
  key.groupID = 0x40464100;
  if (mLayout.Init(&key, 1, 0x5b598f7)) {
    UTFWin::IWindow* const pText = mLayout.FindWindowByID(0x7f869a8, 1);
    if (pText) SPUIHelpers::AutoSizeWindowForText(pText, 1, 0);
    UTFWin::IWindow* const pFrame = mLayout.FindWindowByID(0x7f86a40, 1);
    if (pFrame) {
      pFrame->AddWinProc((UTFWin::IWinProc*)this);
      return true;
    }
    mLayout.Shutdown(1);
  }
  return false;
}

// @ 0x0060b5e0
void cInsertDiscDialog::Show(void* pWinProc, uint32_t captionInstanceID) {
  UTFWin::IWindow* const pFrame = mLayout.FindWindowByID(0x7f86a40, 1);
  if (pFrame) {
    UTFWin::IWindow* const pCaption = mLayout.FindWindowByID(0x7f869f8, 1);
    if (pCaption) {
      SP::cString text;
      text.Load(0x91eecf98, captionInstanceID, 0);
      pCaption->SetCaption(text.GetText());
    }
    SPUIHelpers::BeginModal(pFrame, pWinProc, 1);
  }
}

class __declspec(novtable) IPromptA {
 public:
  virtual void a0() = 0;
};
class __declspec(novtable) IPromptB {
 public:
  virtual void b0() = 0;
};
class cPromptCaster : public IPromptA, public IPromptB {
 public:
  // @ 0x0060b670
  void* Cast(uint32_t typeID);
  virtual void a0();
  virtual void b0();
};
void* cPromptCaster::Cast(uint32_t typeID) {
  if (typeID == 0xee3f516e) return this;
  if (typeID != 0x2f009dd0) return typeID == 0x35ec342a ? this : 0;
  return static_cast<IPromptB*>(this);
}

class __declspec(novtable) IListenerP0 {
 public:
  virtual void p0() = 0;
};
class IListenerP1 {
 public:
  ~IListenerP1() {}
  virtual void p1() = 0;
};
class IListenerP2 {
 public:
  ~IListenerP2() {}
  virtual void p2() = 0;
};
class cListenerP3 : public IMessageListener {
 public:
  virtual void p3();
};
class cPromptListener : public IListenerP0, public IListenerP1, public IListenerP2, public cListenerP3 {
 public:
  // @ 0x0060b6b0
  bool Register();
  virtual void p0();
  virtual void p1();
  virtual void p2();
};
bool cPromptListener::Register() {
  IMessageServer* const pServer = SP::MessageServer();
  if (pServer) {
    pServer->AddListener(static_cast<cListenerP3*>(this), 0x49a32cb);
    pServer->AddListener(static_cast<cListenerP3*>(this), 0x238de9c);
  }
  return true;
}

struct UIMessage {
  UTFWin::IWindow* mpSource;  // +0x0
  uint32_t pad4;
  uint32_t mType;             // +0x8
};
class cPromptHandler {
 public:
  // @ 0x0060b710
  bool HandleUIMessage(UTFWin::IWindow* pWindow, UIMessage* pMessage);
  void* v0;
};
bool cPromptHandler::HandleUIMessage(UTFWin::IWindow* pWindow, UIMessage* pMessage) {
  if (pMessage->mType == 0x287259f6) pMessage->mpSource->GetControlID();
  return false;
}

}  // namespace UI
