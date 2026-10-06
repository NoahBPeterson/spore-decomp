// Slice s00945ed0 -- EA::Internet (UTFInternet): HTTPClient worker thread, POST body streams.
// Module flags: /O2 /MD /Gy /EHsc /TP /GS-
#include "types.h"
#include <intrin.h>

extern "C" {
__declspec(dllimport) void* __cdecl memmove(void*, const void*, unsigned int);
__declspec(dllimport) int __cdecl strncmp(const char*, const char*, unsigned int);
}
void* __cdecl memcpy(void*, const void*, unsigned int);
void __cdecl operator_delete__(void*) throw();
void* __cdecl operator new(unsigned int, const char*, int, int, int, int);

typedef int  (__thiscall *VF0)(void*);
typedef int  (__thiscall *VF1)(void*, int);
typedef int  (__thiscall *VF2)(void*, int, int);
#define VSLOT(p, byteoff) ((*(void***)(p))[(byteoff) / 4])
#define VCALL0(p, off)          ((VF0)VSLOT(p, off))(p)
#define VCALL1(p, off, a)       ((VF1)VSLOT(p, off))(p, (int)(a))
#define VCALL2(p, off, a, b)    ((VF2)VSLOT(p, off))(p, (int)(a), (int)(b))

namespace eastl {
struct StrStub {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    int   mAlloc;
    void assign(const char* first, const char* last);
    void append(const char* first, const char* last);
    ~StrStub() {
        if (mpCapacity - mpBegin > 1 && mpBegin)
            operator_delete__(mpBegin);
    }
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    const char* data() const { return mpBegin; }
};
}

namespace EA { namespace Internet {

void __cdecl EncodeFormURL(const char* s, eastl::StrStub* out);

// ---------------------------------------------------------------------------
// HTTPFormURLEncodedPostBodyStream
// ---------------------------------------------------------------------------
struct IStr {
    virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual int  GetState();                        // 5  (+0x14)
    virtual void v6();
    virtual unsigned GetSize();                     // 7  (+0x1c)
    virtual void v8();
    virtual int  GetPos(int);                       // 9  (+0x24)
    virtual bool SetPos(int, int);                  // 10 (+0x28)
    virtual void v11(); virtual void v12(); virtual void v13();
    virtual int  Write(const void*, unsigned);      // 14 (+0x38)
};
struct IStreamBase {
    virtual ~IStreamBase() {}
    virtual void v1(); virtual void v2(); virtual void v3(); virtual void v4();
    virtual void v5(); virtual void v6(); virtual void v7(); virtual void v8(); virtual void v9();
    virtual void v10();
    virtual int  VGetAvailable();                   // 11 (+0x2c)
    virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15(); virtual void v16();
    virtual void v17(); virtual void v18(); virtual void v19(); virtual void v20(); virtual void v21();
    virtual void WriteStr(const char*, IStr*);      // 22 (+0x58)
    virtual bool Finish();                          // 23 (+0x5c)
    virtual bool Finish2();                         // 24 (+0x60)
};
struct RefCountBase {
    RefCountBase() { _InterlockedExchange((volatile long*)&mnRefCount, 0); }
    virtual ~RefCountBase() {}
    int mnRefCount;
};

class HTTPFormURLEncodedPostBodyStream : public IStreamBase, public RefCountBase {
public:
    long mnPosition;            // +0xc
    int  mnState;               // +0x10
    eastl::StrStub msData;      // +0x14
    bool mbFinal;               // +0x24

    bool Fn9467b0(int);
    bool Fn9467c0();
    bool Fn9467d0(int, int);
    bool Close();
    int  GetSize();
    int  GetPosition(int origin);
    bool SetPosition(int pos, int origin);
    int  GetAvailable();
    int  Read(void* buf, unsigned n);
    bool GetContentTypeString(eastl::StrStub* out);
    bool Write(const char* name, const char* value);
    bool Fn946cc0();
    HTTPFormURLEncodedPostBodyStream();
};

bool HTTPFormURLEncodedPostBodyStream::Fn9467b0(int) { mnState = -1; return false; }
bool HTTPFormURLEncodedPostBodyStream::Fn9467c0() { mnState = -1; return false; }
bool HTTPFormURLEncodedPostBodyStream::Fn9467d0(int, int) { mnState = -1; return false; }

bool HTTPFormURLEncodedPostBodyStream::Close() {
    mnState = -2;
    _ReadWriteBarrier();
    if (msData.mpBegin != msData.mpEnd) {
        *msData.mpBegin = 0;
        msData.mpEnd = msData.mpBegin;
    }
    return true;
}

int HTTPFormURLEncodedPostBodyStream::GetSize() {
    if (!mbFinal)
        return -1;
    if (mnState != 0)
        return -1;
    return (int)(msData.mpEnd - msData.mpBegin);
}

int HTTPFormURLEncodedPostBodyStream::GetPosition(int origin) {
    int r = -1;
    if (mbFinal && mnState == 0) {
        if (origin == 0)
            return mnPosition;
        if (origin == 1)
            return 0;
        if (origin == 2)
            r = mnPosition - (int)msData.mpEnd + (int)msData.mpBegin;
    }
    return r;
}

bool HTTPFormURLEncodedPostBodyStream::SetPosition(int pos, int origin) {
    unsigned p = 0;
    if (!mbFinal)
        mbFinal = true;
    if (origin == 0)
        p = pos;
    else if (origin == 1)
        p = mnPosition + pos;
    else if (origin == 2)
        p = (msData.mpEnd - msData.mpBegin) + pos;
    else
        mnState = -1;
    if (p > (unsigned)(msData.mpEnd - msData.mpBegin) || (int)p < 0)
        mnState = -1;
    if (mnState != 0)
        return false;
    mnPosition = p;
    return true;
}

int HTTPFormURLEncodedPostBodyStream::GetAvailable() {
    if (!mbFinal)
        return -1;
    if (mnState != 0)
        return -1;
    return (msData.mpEnd - mnPosition) - msData.mpBegin;
}

int HTTPFormURLEncodedPostBodyStream::Read(void* buf, unsigned n) {
    int r = -1;
    if (buf == 0)
        mnState = r;
    if (!mbFinal)
        mbFinal = true;
    if (mnState == 0) {
        unsigned avail = (unsigned)VGetAvailable();
        n = n > avail ? avail : n;
        memcpy(buf, msData.mpBegin + mnPosition, n);
        mnPosition += n;
        return n;
    }
    return r;
}

bool HTTPFormURLEncodedPostBodyStream::GetContentTypeString(eastl::StrStub* out) {
    static const char s[] = "application/x-www-form-urlencoded";
    out->assign(s, s + 33);
    return true;
}

bool HTTPFormURLEncodedPostBodyStream::Write(const char* name, const char* value) {
    int neg = -1;
    if (mbFinal)
        mnState = neg;
    if (name == 0)
        mnState = neg;
    if (mnState != 0)
        return false;
    eastl::StrStub& d = msData;
    if (d.mpBegin != d.mpEnd)
        d.append("&", "&" + 1);
    EncodeFormURL(name, &d);
    d.append("=", "=" + 1);
    if (value)
        EncodeFormURL(value, &d);
    return true;
}

bool HTTPFormURLEncodedPostBodyStream::Fn946cc0() { mbFinal = true; return true; }

HTTPFormURLEncodedPostBodyStream::HTTPFormURLEncodedPostBodyStream() {
    mnPosition = 0;
    mnState = 0;
    _ReadWriteBarrier();
    msData.mpBegin = (char*)0x1667bac;
    msData.mpEnd = (char*)0x1667bac;
    msData.mpCapacity = (char*)0x1667bad;
    mbFinal = false;
}



// ---------------------------------------------------------------------------
// Multipart streams
// ---------------------------------------------------------------------------
struct ListNode {
    ListNode* next;
    ListNode* prev;
};
struct StreamNode : ListNode {
    IStr*     stream;
};

class HTTPMultipartFormDataPostBodyStream : public IStreamBase, public RefCountBase {
public:
    ListNode mListAnchor;       // +0xc
    int      mListSize;         // +0x14
    eastl::StrStub msBoundary;  // +0x18
    ListNode* mReadItr;         // +0x28
    long     mnPosition;        // +0x2c
    unsigned mnSize;            // +0x30
    int      mnState;           // +0x34
    bool     mbFinal;           // +0x38
    int      mLastDataType;     // +0x3c
    unsigned mnTextStart;       // +0x40
    IStr*    mpMemStream;       // +0x44

    int  GetSize();
    bool Finalize();
    bool WriteField(const char* name, const char* value);
    bool WriteEndBoundary();
};

class HTTPMultipartRelatedPostBodyStream : public IStreamBase, public RefCountBase {
public:
    ListNode mListAnchor;       // +0xc
    int      mListSize;         // +0x14
    eastl::StrStub msBoundary;  // +0x18
    ListNode* mReadItr;         // +0x28
    long     mnPosition;        // +0x2c
    unsigned mnSize;            // +0x30
    int      mnState;           // +0x34
    bool     mbFinal;           // +0x38
    int      mLastDataType;     // +0x3c
    unsigned mnTextStart;       // +0x40
    IStr*    mpMemStream;       // +0x44

    bool SetSize(int);
    bool SetPosition(int pos, int origin);
};

int HTTPMultipartFormDataPostBodyStream::GetSize() {
    if (!mbFinal)
        return -1;
    if (mnState != 0)
        return -1;
    return mnSize;
}

bool HTTPMultipartRelatedPostBodyStream::SetSize(int) {
    mnState = -1;
    return false;
}

bool HTTPMultipartFormDataPostBodyStream::Finalize() {
    if (!mbFinal && mnState != -1) {
        if (mpMemStream->GetPos(0) > 0) {
            mbFinal = Finish();
            mnPosition = 0;
            return mbFinal;
        }
        mbFinal = true;
        mnPosition = 0;
    }
    return mbFinal;
}

bool HTTPMultipartFormDataPostBodyStream::WriteField(const char* name, const char* value) {
    if (mbFinal)
        mnState = -1;
    if (name == 0)
        mnState = -1;
    if (mnState == 0) {
        unsigned pos = mpMemStream->GetPos(0);
        if (mLastDataType == 1) {
            mnTextStart = pos;
            mLastDataType = 0;
        }
        WriteStr((const char*)0x13fb644, mpMemStream);
        mpMemStream->Write(msBoundary.data(), msBoundary.size());
        WriteStr((const char*)0x13fb618, mpMemStream);
        WriteStr(name, mpMemStream);
        WriteStr((const char*)0x13fb610, mpMemStream);
        WriteStr(value, mpMemStream);
        if (mpMemStream->GetState() != 0)
            mnState = -1;
        else
            return true;
    }
    return false;
}

bool HTTPMultipartFormDataPostBodyStream::WriteEndBoundary() {
    if (mpMemStream) {
        unsigned pos = mpMemStream->GetPos(0);
        if (mLastDataType == 1) {
            mnTextStart = pos;
            mLastDataType = 0;
        }
        WriteStr((const char*)0x13fb644, mpMemStream);
        mpMemStream->Write(msBoundary.data(), msBoundary.size());
        WriteStr((const char*)0x13fb688, mpMemStream);
        if (mpMemStream->GetState() != 0)
            mnState = -1;
        else {
            mLastDataType = 0;
            return Finish2();
        }
    }
    return false;
}

bool HTTPMultipartRelatedPostBodyStream::SetPosition(int pos, int origin) {
    if (mnState != 0)
        return false;
    if (!mbFinal)
        mbFinal = true;
    unsigned target;
    if (origin == 0)
        target = pos;
    else if (origin == 1)
        target = mnPosition + pos;
    else if (origin == 2)
        target = mnSize + pos;
    else {
        mnState = -1;
        return false;
    }
    if (target > mnSize || (int)target < 0) {
        mnState = -1;
        return false;
    }
    ListNode* end = &mListAnchor;
    ListNode* node = mListAnchor.next;
    unsigned total = 0;
    if (((StreamNode*)node)->stream->GetSize() < target) {
        do {
            total += ((StreamNode*)node)->stream->GetSize();
            node = node->next;
            if (node == end) {
                mnState = -1;
                return false;
            }
        } while (((StreamNode*)node)->stream->GetSize() + total < target);
    }
    if (!((StreamNode*)node)->stream->SetPos(target - total, 0)) {
        mnState = -1;
        return false;
    }
    ListNode* cur = node;
    node = node->next;
    while (node != end) {
        if (!((StreamNode*)node)->stream->SetPos(0, 0)) {
            mnState = -1;
            return false;
        }
        node = node->next;
    }
    mReadItr = cur;
    mnPosition = target;
    return true;
}


// ---------------------------------------------------------------------------
// HTTPClient: worker thread, job queueing
// ---------------------------------------------------------------------------
struct Mutex {
    void Lock(const void* timeout);
    void Unlock();
};
struct Thread {
    Thread();
    void Begin(void* fn, void* arg, int, int prio);   // FUN_00922f30
    void WaitForEnd();                                // FUN_00922e10
};
int GetThreadPriorityDefault();                       // FUN_00922920
void __cdecl ThreadSleep(const void* t);              // EA::Thread::ThreadSleep
int __cdecl GetTime64();                              // FUN_00941bb0
char* __cdecl Sprintf8(char* buf, const char* fmt, ...);
const char* __cdecl HeaderFieldToFieldString(int field);
extern char g_logBuf[];                               // 0x0166A9D8
extern const int kLockTimeout;                        // 0x0143F214
extern const int kSleepTime;                          // 0x0143F218

class HTTPClient;

template <class T>
struct AutoRefCount {
    T* mp;
    AutoRefCount() : mp(0) {}
    void Set(T* p);                  // out of line (AddRef new, Release old): FUN_008fd240
};

struct IUnkStub {
    virtual int AddRef();
    virtual int Release();
};
struct ISockOpt {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8(); virtual void s9();
    virtual void s10(); virtual void s11();
    virtual void Shutdown(int how);         // slot 12 (+0x30)
};
struct ISock : IUnkStub {
    virtual void s2();
    virtual void s3();
    virtual ISockOpt* GetOptions();         // slot 4 (+0x10)
};

// Intrusive refcounted object whose deleting destructor is vtable slot 0 and whose count is at +4.
struct RefObj {
    virtual void Destroy(int flags);
    int mnRefCount;
};
inline void ReleaseRefObj(RefObj* p) {
    if (p) {
        int n = _InterlockedExchangeAdd((volatile long*)&p->mnRefCount, -1);
        if (n - 1 == 0) {
            _InterlockedExchange((volatile long*)&p->mnRefCount, 1);
            if (p)
                p->Destroy(1);
        }
    }
}

struct IFilter {
    virtual void f0();
    virtual void f1();
    virtual bool OnResponse(void* resp);    // slot 2 (+8)
    virtual bool OnRequest(void* req);      // slot 3 (+0xc)
};
struct IRef3 {
    virtual void f0();
    virtual void AddRef();                  // +4
    virtual void Release();                 // +8
};
struct IBodyStream {
    virtual void f0(); virtual void f1(); virtual void f2(); virtual void f3(); virtual void f4(); virtual void f5();
    virtual void Close();                   // slot 6 (+0x18)
};
struct IChecker {
    virtual void f0();
    virtual bool Check(void* resp);         // slot 1 (+4)
};

struct HeaderList {
    bool FindHeader(const char* name, const char** out, int);   // FUN_00942050
};

struct HTTPResponse {
    int  pad0[2];
    eastl::StrStub msBody;           // +8   (basic_string head only)
    char pad1[0x21c - 0x18];
    eastl::StrStub msStr21c;         // +0x21c
    char pad2[0x430 - 0x22c];
    int  nStatus;                    // +0x430
    unsigned nMajor;                 // +0x434
    unsigned nMinor;                 // +0x438
    int  nHasHeaders;                // +0x43c
    char pad3[0x4a4 - 0x440];
    HeaderList headers;              // +0x4a4
    char pad4[0xf3c - 0x4a5];
    IRef3* mpExtra;                  // +0xf3c
    HTTPResponse();                  // FUN_00943de0, 0xf40-byte object
};

struct UrlHolder {
    eastl::StrStub* GetString();     // FUN_0097e850 (symbol name there is misattributed)
};
struct HTTPRequestStub {
    char pad0[8];
    char* mpUrlBegin;                // +8
    char* mpUrlEnd;                  // +0xc
    char pad1[0x30 - 0x10];
    UrlHolder urlHolder;             // +0x30
    char pad2[0xe0 - 0x31];
    eastl::StrStub msStrE0;          // +0xe0
    char pad3[0xd8c - 0xf0];
    IBodyStream* mpBody;             // +0xd8c
    IRef3* mpExtra;                  // +0xd90
    IChecker* mpChecker;             // +0xd94
};

struct Job {
    unsigned id;                     // +0
    int      state;                  // +4
    int      userData;               // +8  (timeout seconds)
    int      z0;                     // +0xc (deadline)
    int      one;                    // +0x10
    int      z1;                     // +0x14 (progress)
    int      z2;                     // +0x18
    AutoRefCount<HTTPRequestStub> mpRequest;   // +0x1c
    bool     bFlag;                  // +0x20
    AutoRefCount<HTTPResponse> mpResponse;     // +0x24
    int      arg;                    // +0x28
    int      pad2c;                  // +0x2c
    int      z3[4];                  // +0x30
    Job() {}
    ~Job();                              // FUN_00942630
    void Assign(const Job* o);           // FUN_00942d70
};

struct JobNode {
    JobNode* next;
    JobNode* prev;
    Job job;                         // +8
};

struct EmptyStr : eastl::StrStub {
    EmptyStr() {
        mpBegin = (char*)0x1667bac;
        mpEnd = (char*)0x1667bac;
        mpCapacity = (char*)0x1667bad;
    }
};

struct WorkerThreadInfo {
    HTTPClient* mpOwner;             // +0
    bool bCreated;                   // +4
    bool bShouldQuit;                // +5
    bool bCancel;                    // +6
    int  pauseCount;                 // +8
    EmptyStr msServer;               // +0xc
    unsigned short nPort;            // +0x1c
    ISock* mpSocket;                 // +0x20
    int  protocol;                   // +0x24
    bool bV11;                       // +0x28
    Job* mpCurrentJob;               // +0x2c
    Thread mThread;                  // +0x30
    WorkerThreadInfo() : mpOwner(0), mpSocket(0) {}
};

struct JobListAnchor {
    JobNode* next;
    JobNode* prev;
    void Push(const Job* j);         // FUN_00943600 (list push_back)
};

typedef void (__cdecl *NotifyFn)(void* ctx, void* client, unsigned msg, void* data, int zero);

class HTTPClient : public IUnkStub {
public:
    int  pad4[2];                    // +4,+8
    bool mbInitialized;              // +0xc
    char pad1[0x24 - 0x10];
    NotifyFn mpNotify;               // +0x24
    void* mpNotifyCtx;               // +0x28
    int  mnLastJobId;                // +0x2c
    int  mnLoggingEnabled;           // +0x30
    char pad5[0x54 - 0x34];
    IStr* mpLogB;                    // +0x54
    IStr* mpLogA;                    // +0x58
    char pad2[0x60 - 0x5c];
    Mutex mMutex;                    // +0x60
    char pad3[0x90 - 0x61];
    WorkerThreadInfo* mpWorkerThreadInfo;   // +0x90
    JobListAnchor mJobList;          // +0x94
    char pad6[0x128 - 0x9c];
    int  mnDefaultTimeout;           // +0x128
    char pad7[0x150 - 0x12c];
    IFilter** mpFiltersBegin;        // +0x150
    IFilter** mpFiltersEnd;          // +0x154

    void CreateWorkerThreadIfNeeded();
    unsigned AddNewJob(HTTPRequestStub* req, int arg3, bool arg4, int arg5);
    unsigned WorkerThreadFunction(WorkerThreadInfo* info);
    static unsigned StaticWorkerThreadFunction(WorkerThreadInfo* info);

    bool Fn942ff0(WorkerThreadInfo* info);
    bool Fn944f40(WorkerThreadInfo* info);
    bool Fn944e10(WorkerThreadInfo* info, int);
    bool WriteRequestBody(WorkerThreadInfo* info);
    bool Fn9453f0(WorkerThreadInfo* info);
    bool ReadResponseBody(WorkerThreadInfo* info);
    int  Fn945a10(WorkerThreadInfo* info);
    void Pump(ISock* socket);
};

unsigned HTTPClient::StaticWorkerThreadFunction(WorkerThreadInfo* info) {
    HTTPClient* c = info->mpOwner;
    unsigned r = c->WorkerThreadFunction(info);
    c->Release();
    return r;
}

void HTTPClient::CreateWorkerThreadIfNeeded() {
    mMutex.Lock(&kLockTimeout);
    if (mpWorkerThreadInfo == 0) {
        WorkerThreadInfo* p = new("UTFInternet/WorkerThreadInfo", 0, 0, 0, 0) WorkerThreadInfo;
        mpWorkerThreadInfo = p;
        HTTPClient* old = p->mpOwner;
        if (this != old) {
            AddRef();
            p->mpOwner = this;
            if (old)
                old->Release();
        }
        mpWorkerThreadInfo->bCreated = false;
        mpWorkerThreadInfo->bShouldQuit = false;
        mpWorkerThreadInfo->bCancel = false;
        mpWorkerThreadInfo->pauseCount = 0;
        ISock** slot = &mpWorkerThreadInfo->mpSocket;
        ISock* sock = *slot;
        if (sock) {
            *slot = 0;
            sock->Release();
        }
        mpWorkerThreadInfo->protocol = 0;
        mpWorkerThreadInfo->mpCurrentJob = 0;
        mpWorkerThreadInfo->bV11 = true;
        mpWorkerThreadInfo->nPort = 0;
    }
    mpWorkerThreadInfo->bShouldQuit = false;
    if (!mpWorkerThreadInfo->bCreated) {
        mpWorkerThreadInfo->bCreated = true;
        AddRef();
        WorkerThreadInfo* info = mpWorkerThreadInfo;
        info->mThread.Begin((void*)StaticWorkerThreadFunction, info, 0, GetThreadPriorityDefault());
    }
    mMutex.Unlock();
}

unsigned HTTPClient::AddNewJob(HTTPRequestStub* req, int arg3, bool arg4, int arg5) {
    if (!mbInitialized)
        return 0;
    if (req == 0 || !(req->mpUrlEnd - req->mpUrlBegin))
        return 0;
    eastl::StrStub* host = req->urlHolder.GetString();
    if (host->mpBegin == host->mpEnd)
        return 0;
    Job job;
    job.state = 1;
    job.userData = arg5;
    job.z0 = 0;
    job.one = 1;
    job.z2 = 0;
    job.z1 = 0;
    job.mpRequest.Set(req);
    job.bFlag = arg4;
    job.mpResponse.Set(new("UTFInternet/WorkerThreadInfo", 0, 0, 0, 0) HTTPResponse);
    job.arg = arg3;
    job.z3[0] = 0;
    job.z3[1] = 0;
    job.z3[2] = 0;
    job.z3[3] = 0;
    mMutex.Lock(&kLockTimeout);
    ++mnLastJobId;
    unsigned id = mnLastJobId;
    job.id = id;
    mJobList.Push(&job);
    mMutex.Unlock();
    CreateWorkerThreadIfNeeded();
    return id;
}

// Shared by the two "compact the receive buffer" tails of WorkerThreadFunction:
// erase the whole receive buffer (info+0xc..+0x10) the way basic_string::erase(begin, begin + min(size, npos)) does.
static inline const char* CharStrEnd(const char* p) {
    const char* e = p;
    while (*e++)
        ;
    return e - 1;
}

unsigned HTTPClient::WorkerThreadFunction(WorkerThreadInfo* info) {
    Job job;
    bool bOk;
    bool bClose;
    unsigned npos;
    unsigned sz;
    unsigned* pmin;

    Mutex* pMutex = &mMutex;
    info->bV11 = true;
    pMutex->Lock(&kLockTimeout);
    while (!info->bShouldQuit) {
        pMutex->Unlock();
        if (info->pauseCount > 0) {
            ThreadSleep(&kSleepTime);
            goto relock;
        }
        pMutex->Lock(&kLockTimeout);
        if ((void*)mJobList.next == (void*)&mJobList)
            break;
        bOk = true;
        bClose = false;
        job.Assign(&mJobList.next->job);
        {
            JobNode* node = mJobList.next;
            node->prev->next = node->next;
            node->next->prev = node->prev;
            ReleaseRefObj((RefObj*)node->job.mpResponse.mp);
            ReleaseRefObj((RefObj*)node->job.mpRequest.mp);
            operator_delete__(node);
        }
        info->mpCurrentJob = &job;
        if (mnLoggingEnabled > 0) {
            Sprintf8(g_logBuf, "\r\n--- New Job ( %d ) ------------------------------------------------------\r\n", job.id);
            if (mnLoggingEnabled > 0)
                mpLogA->Write(g_logBuf, CharStrEnd(g_logBuf) - g_logBuf);
            if (mnLoggingEnabled > 0)
                mpLogB->Write(g_logBuf, CharStrEnd(g_logBuf) - g_logBuf);
        }
        {
            int now = GetTime64();
            int t = job.userData;
            if (t == 0) {
                t = mnDefaultTimeout;
                job.userData = t;
            }
            if (t > 0)
                t += now;
            job.z0 = t;
        }
        pMutex->Unlock();
        for (IFilter** f = mpFiltersBegin; f != mpFiltersEnd; ++f) {
            if (!(*f)->OnRequest(job.mpRequest.mp)) {
                bOk = false;
                break;
            }
        }
        {
            const char* url = *(const char**)job.mpRequest.mp->urlHolder.GetString();
            eastl::StrStub& body = job.mpResponse.mp->msBody;
            if (body.mpBegin != url) {
                if (body.mpBegin != body.mpEnd) {
                    *body.mpBegin = 0;
                    body.mpEnd = body.mpBegin;
                }
                body.append(url, CharStrEnd(url));
            }
        }
        {
            eastl::StrStub* dst = &job.mpResponse.mp->msStr21c;
            eastl::StrStub* src = &job.mpRequest.mp->msStrE0;
            if (dst != src) {
                if (dst->mpBegin != dst->mpEnd) {
                    *dst->mpBegin = 0;
                    dst->mpEnd = dst->mpBegin;
                }
                dst->append(src->mpBegin, src->mpEnd);
            }
        }
        {
            IRef3* newp = job.mpRequest.mp->mpExtra;
            IRef3* oldp = job.mpResponse.mp->mpExtra;
            IRef3** slot = &job.mpResponse.mp->mpExtra;
            if (newp != oldp) {
                if (newp)
                    newp->AddRef();
                *slot = newp;
                if (oldp)
                    oldp->Release();
            }
        }
        if (!Fn942ff0(info))
            goto fail;
        if (!bOk)
            goto afterBody;
        if (!Fn944f40(info)) {
        retry:
            if (Fn944e10(info, 1))
                goto relock;
            goto fail;
        }
        if (info->bCancel || info->bShouldQuit)
            goto fail;
        if (job.mpRequest.mp->mpBody != 0) {
            if (!WriteRequestBody(info))
                goto retry;
            if (info->bCancel || info->bShouldQuit)
                goto fail;
        }
        if (job.mpResponse.mp->nHasHeaders == 0) {
            if (!Fn9453f0(info))
                goto retry;
        }
        if (info->bCancel || info->bShouldQuit)
            bOk = false;
        {
            HTTPResponse* r = job.mpResponse.mp;
            bool v11;
            if (r->nMajor > 1)
                v11 = true;
            else if (r->nMajor < 1)
                v11 = false;
            else
                v11 = r->nMinor >= 1;
            info->bV11 = v11;
        }
        {
            const char* val;
            if (job.mpResponse.mp->headers.FindHeader(HeaderFieldToFieldString(2), &val, 0)) {
                if (strncmp(val, "close", 5) == 0)
                    bClose = true;
            }
        }
        if (!bOk)
            goto afterBody;
        {
            IChecker* chk = job.mpRequest.mp->mpChecker;
            if (chk && !chk->Check(job.mpResponse.mp)) {
                job.state = 0xe;
                goto fail;
            }
        }
        if (!ReadResponseBody(info))
            goto retry;
        if (!info->bCancel && !info->bShouldQuit)
            goto afterBody;
    fail:
        bOk = false;
    afterBody:
        for (IFilter** f = mpFiltersBegin; f != mpFiltersEnd; ++f) {
            if (!(*f)->OnResponse(job.mpResponse.mp)) {
                bOk = false;
                goto tail;
            }
        }
        if (bOk && Fn945a10(info) == 1) {
            char* b = (char*)info->msServer.mpBegin;
            sz = info->msServer.mpEnd - b;
            npos = 0xffffffff;
            pmin = &sz;
            if (sz >= 0xffffffff)
                pmin = &npos;
            char* last = b + *pmin;
            if (b != last) {
                memmove(b, last, (info->msServer.mpEnd - last) + 1);
                info->msServer.mpEnd = b + (info->msServer.mpEnd - last);
            }
            info->nPort = 0;
            Pump(info->mpSocket);
            goto relock;
        }
    tail:
        if (!info->bCancel && !info->bShouldQuit) {
            if (!bOk)
                goto compact;
            if (bClose) {
                Pump(info->mpSocket);
                goto notify;
            }
            goto notify;
        } else {
            info->bCancel = false;
            job.state = 8;
        }
    compact:
        {
            char* b = (char*)info->msServer.mpBegin;
            sz = info->msServer.mpEnd - b;
            npos = 0xffffffff;
            pmin = &sz;
            if (sz >= 0xffffffff)
                pmin = &npos;
            char* last = b + *pmin;
            if (b != last) {
                memmove(b, last, (info->msServer.mpEnd - last) + 1);
                info->msServer.mpEnd = b + (info->msServer.mpEnd - last);
            }
            info->nPort = 0;
            Pump(info->mpSocket);
        }
    notify:
        if (!info->bShouldQuit) {
            job.z1 = 100;
            job.mpResponse.mp->nStatus = job.z2;
            if (mpNotify)
                mpNotify(mpNotifyCtx, this, 0x700af301, &job, 0);
        }
        if (job.mpRequest.mp->mpBody && job.bFlag)
            job.mpRequest.mp->mpBody->Close();
        info->mpCurrentJob = 0;
        if (mnLoggingEnabled > 0) {
            mpLogA->Write("\r\n--- End Job ------------------------------------------------------\r\n", 0x46);
            if (mnLoggingEnabled > 0)
                mpLogB->Write("\r\n--- End Job ------------------------------------------------------\r\n", 0x46);
        }
    relock:
        pMutex->Lock(&kLockTimeout);
    }
    mpWorkerThreadInfo = 0;
    if (info->mpSocket) {
        Pump(info->mpSocket);
        info->mpSocket->GetOptions()->Shutdown(2);
    }
    info->mThread.WaitForEnd();
    if (info->mpSocket)
        info->mpSocket->Release();
    if (info->msServer.mpCapacity - info->msServer.mpBegin > 1 && info->msServer.mpBegin)
        operator_delete__(info->msServer.mpBegin);
    if (info->mpOwner)
        info->mpOwner->Release();
    operator_delete__(info);
    pMutex->Unlock();
    return 0;
}

}} // namespace EA::Internet
