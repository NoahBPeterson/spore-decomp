// Batch "gold1" slice s00942ff0 - EA::Internet::HTTPClient Job/WorkerThreadInfo helpers.
// Reconstructed from the original disassembly + Ghidra decompiles (cards in work/match).
// Flags: /O2 /MD /Gy /TP /GS-
#include <intrin.h>
#include <new>
#include "types.h"

// ---------------------------------------------------------------------------
// External helpers / callees (defined elsewhere in the image).
// ---------------------------------------------------------------------------
extern "C" void __cdecl operator_delete__(void* p);   // 0x00f47380
void* __cdecl operator_new(unsigned int size, const char* name, int a, int b,
                           const char* file, int line);   // 0x00f473a0
extern "C" unsigned int __cdecl strlen(const char* s);

// ---------------------------------------------------------------------------
// eastl::basic_string<char> with SSO: 0x14 header + 0x40 inline buffer (0x54).
// ---------------------------------------------------------------------------
namespace eastl {
struct StrStub {
    char* mpBegin;      // +0x00
    char* mpEnd;        // +0x04
    char* mpCapacity;   // +0x08
    int   mnAllocPad;   // +0x0c
    char* mpSelf;       // +0x10  (points at mBuffer)
    char  mBuffer[0x40];// +0x14
    StrStub() {}                                        // (not emitted: no default use)
    StrStub(const StrStub& o) {                         // SSO copy ctor
        mpSelf = mBuffer;
        mpCapacity = mBuffer + 0x40;
        mpEnd = mBuffer;
        mpBegin = mBuffer;
        *mBuffer = 0;
        assignRange(o.mpBegin, o.mpEnd);
    }
    StrStub& operator=(const StrStub& o) {
        if (this != &o) {
            if (mpBegin != mpEnd) {
                *mpBegin = 0;
                mpEnd = mpBegin;
            }
            assignRange(o.mpBegin, o.mpEnd);
        }
        return *this;
    }
    void assignRange(const char* first, const char* last);   // 0x00942E50 (slice 49)
    StrStub* assign(const char* s);                          // 0x00943570
};
}

typedef eastl::StrStub JobString;

// eastl::pair<StrStub,StrStub> == the job record (0xa8).
struct Job {
    JobString first;    // +0x00
    JobString second;   // +0x54
    Job(const Job& s);                  // 0x00943650
    Job& operator=(const Job& s);       // 0x009436B0
};

// Intrusive refcounted object: vtable slot 0 is the deleting destructor, count at +4.
struct RefObj {
    virtual void Destroy(int flags);
    int mnRefCount;
    __forceinline void Release() {
        int rc = _InterlockedDecrement((volatile long*)&mnRefCount);
        if (rc == 0) {
            _InterlockedExchange((volatile long*)&mnRefCount, 1);
            if (this)
                Destroy(1);
        }
    }
};
inline void ReleaseRefObj(RefObj* p) {
    if (p) {
        int rc = _InterlockedDecrement((volatile long*)&p->mnRefCount);
        if (rc == 0) {
            _InterlockedExchange((volatile long*)&p->mnRefCount, 1);
            if (p)
                p->Destroy(1);
        }
    }
}

// Cookie40 is 0x40 bytes (see slice 49): two refcounted pointers at +0x1c / +0x24.
struct Cookie40 {
    int      m00[7];      // +0x00
    RefObj*  mp1c;        // +0x1c
    int      m20;         // +0x20
    RefObj*  mp24;        // +0x24
    int      m28;         // +0x28
    int      m2c;         // +0x2c
    unsigned __int64 m30; // +0x30
    unsigned __int64 m38; // +0x38
    Cookie40(const Cookie40&);   // 0x00942CE0 (slice 49)
};

// Intrusive doubly-linked list node holding a Cookie40 payload at +8 (total 0x48).
struct CookieNode {
    CookieNode* mpNext;   // +0x00
    CookieNode* mpPrev;   // +0x04
    Cookie40    mData;    // +0x08
    void insertBeforeSelf(const Cookie40& src);   // 0x00943600
};

// eastl list<Cookie40> head wrapper (mpNode = sentinel).
struct CookieList {
    CookieNode* mpNode;   // +0x00
    void insertAtNext(const Cookie40& src);       // 0x009435B0
};

// ---------------------------------------------------------------------------
// @ 0x00943570  eastl::StrStub::assign(const char*)  (returns this)
// ---------------------------------------------------------------------------
eastl::StrStub* eastl::StrStub::assign(const char* s) {
    if (mpBegin != s) {
        if (mpBegin != mpEnd) {
            *mpBegin = 0;
            mpEnd = mpBegin;
        }
        assignRange(s, s + strlen(s));
    }
    return this;
}

// ---------------------------------------------------------------------------
// @ 0x00943420  destroy a [first,last) range of Job records (pair<StrStub,StrStub>)
// ---------------------------------------------------------------------------
static void DestroyJobString(eastl::StrStub& s) {
    char* b = s.mpBegin;
    if ((int)(s.mpCapacity - b) > 1 && b != 0 && b != s.mpSelf)
        operator_delete__(b);
}

void __stdcall JobDestroyRange(Job* first, Job* last) {
    for (; first < last; first = (Job*)((char*)first + 0xa8)) {
        char* b = first->second.mpBegin;
        if ((int)(first->second.mpCapacity - b) > 1 && b != 0 && b != first->second.mpSelf)
            operator_delete__(b);
        char* a = first->first.mpBegin;
        if ((int)(first->first.mpCapacity - a) > 1 && a != 0 && a != first->first.mpSelf)
            operator_delete__(a);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00943480  eastl list<Cookie40> destructor (ecx = head sentinel)
// ---------------------------------------------------------------------------
void __fastcall ListDestroy(CookieNode* head) {
    CookieNode* n = head->mpNext;
    while (n != head) {
        CookieNode* next = n->mpNext;
        ReleaseRefObj(n->mData.mp24);
        ReleaseRefObj(n->mData.mp1c);
        operator_delete__(n);
        n = next;
    }
}

// ---------------------------------------------------------------------------
// @ 0x00943500  destroy [first,last) Job records while walking dst; returns dst
// ---------------------------------------------------------------------------
Job* JobDestroyRangeDst(Job* first, Job* last, Job* dst) {
    if (first != last) {
        do {
            char* b = first->second.mpBegin;
            if ((int)(first->second.mpCapacity - b) > 1 && b != 0 && b != first->second.mpSelf)
                operator_delete__(b);
            char* a = first->first.mpBegin;
            if ((int)(first->first.mpCapacity - a) > 1 && a != 0 && a != first->first.mpSelf)
                operator_delete__(a);
            first = (Job*)((char*)first + 0xa8);
            dst = (Job*)((char*)dst + 0xa8);
        } while (first != last);
    }
    return dst;
}

// ---------------------------------------------------------------------------
// @ 0x00943650  eastl::pair<StrStub,StrStub>::pair(const pair&)  (Job copy ctor)
// ---------------------------------------------------------------------------
Job::Job(const Job& s) : first(s.first), second(s.second) {}

// ---------------------------------------------------------------------------
// @ 0x009436B0  eastl::pair<StrStub,StrStub>::operator=(const pair&)
// ---------------------------------------------------------------------------
Job& Job::operator=(const Job& s) {
    first = s.first;
    second = s.second;
    return *this;
}

// ---------------------------------------------------------------------------
// eastl list<Cookie40> node insert helpers.
// ---------------------------------------------------------------------------
static const char kEastlFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
static const char kEastlName[] = "EASTL";

static inline void InsertBefore(CookieNode* at, const Cookie40& src) {
    CookieNode* node = (CookieNode*)operator_new(0x48, kEastlName, 0, 0, kEastlFile, 0xd1);
    new (&node->mData) Cookie40(src);
    node->mpNext = at;
    node->mpPrev = at->mpPrev;
    at->mpPrev->mpNext = node;
    at->mpPrev = node;
}

// @ 0x009435B0  list insert (at = list->mpNext)
void CookieList::insertAtNext(const Cookie40& src) {
    InsertBefore(mpNode, src);
}

// @ 0x00943600  list insert (at = this sentinel)
void CookieNode::insertBeforeSelf(const Cookie40& src) {
    InsertBefore(this, src);
}

// ---------------------------------------------------------------------------
// @ 0x00943710  eastl::uninitialized_copy over Job (construct dst copies)
// ---------------------------------------------------------------------------
Job* UninitializedCopyJob(Job* first, Job* last, Job* dst) {
    if (first != last) {
        do {
            new (dst) Job(*first);
            first = (Job*)((char*)first + 0xa8);
            dst = (Job*)((char*)dst + 0xa8);
        } while (first != last);
    }
    return dst;
}

// ---------------------------------------------------------------------------
// @ 0x009437A0  eastl::copy over Job (assign dst = src)
// ---------------------------------------------------------------------------
Job* CopyJob(Job* first, Job* last, Job* dst) {
    for (; first != last; dst = (Job*)((char*)dst + 0xa8), first = (Job*)((char*)first + 0xa8))
        *dst = *first;
    return dst;
}

// ---------------------------------------------------------------------------
// @ 0x00943830  eastl::copy_backward over Job
// ---------------------------------------------------------------------------
Job* CopyBackwardJob(Job* first, Job* last, Job* dst) {
    while (last != first) {
        last = (Job*)((char*)last - 0xa8);
        dst = (Job*)((char*)dst - 0xa8);
        *dst = *last;
    }
    return dst;
}

// ---------------------------------------------------------------------------
// @ 0x009438C0  EA::Internet::HTTPRequest::SetMethod
// ---------------------------------------------------------------------------
extern "C" const char* HTTPMethodToString(int method);   // 0x00941BC0

// Inline-SSO blob (string or vector): header 0x14 + inline buffer.
template <int N>
struct SsoBlob {
    char* mpBegin;      // +0x00
    char* mpEnd;        // +0x04
    char* mpCapacity;   // +0x08
    int   mnPad;        // +0x0c
    char* mpSelf;       // +0x10
    char  mBuffer[N];   // +0x14
    void init() {
        mpSelf = mBuffer;
        mpEnd = mBuffer;
        mpBegin = mBuffer;
        mpCapacity = mBuffer + N;
        *mBuffer = 0;
    }
    void destroy() {
        char* b = mpBegin;
        if ((int)(mpCapacity - b) > 1 && b != 0 && b != mpSelf)
            operator_delete__(b);
    }
};

// Same header, but the buffer starts at +0x18 (Job element alignment).
struct JobVecBlob {
    Job* mpBegin;           // +0x00
    Job* mpEnd;             // +0x04
    Job* mpCapacity;        // +0x08
    int  m0c;               // +0x0c
    Job* mpSelf;            // +0x10
    int  m14;               // +0x14
    char mBuffer[0xa80];    // +0x18
    void init() {
        mpSelf = (Job*)mBuffer;
        mpEnd = (Job*)mBuffer;
        mpBegin = (Job*)mBuffer;
        mpCapacity = (Job*)(mBuffer + 0xa80);
    }
    void destroyRange() {
        JobDestroyRange(mpBegin, mpEnd);
        Job* b = mpBegin;
        if (b != 0 && b != mpSelf)
            operator_delete__(b);
    }
};

struct HTTPRequest {
    void*              mpVtbl;       // +0x000
    int                mnRefCount;   // +0x004
    SsoBlob<0x200>     mStr08;       // +0x008
    SsoBlob<0x200>     mStr21c;      // +0x21c
    int                m430;         // +0x430
    int                m434;         // +0x434
    int                m438;         // +0x438
    int                m43c;         // +0x43c
    SsoBlob<0x50>      mStr440;      // +0x440
    JobVecBlob         mJobs;        // +0x4a4
    void*              mp3cf;        // +0xf3c
    void SetMethod(int method);   // 0x009438C0
    HTTPRequest();                 // 0x00943DE0
    ~HTTPRequest();                // 0x00943EA0
};

// @ 0x00943DE0  EA::Internet::HTTPRequest::HTTPRequest
HTTPRequest::HTTPRequest() {
    *(void**)this = (void*)0x13fb19c;
    _InterlockedExchange((volatile long*)&mnRefCount, 0);
    *(void**)this = (void*)0x143f238;
    mStr08.init();
    mStr21c.init();
    m430 = 0;
    m434 = -1;
    m438 = -1;
    m43c = 0;
    mStr440.init();
    mJobs.init();
    mp3cf = 0;
}

// @ 0x00943EA0  EA::Internet::HTTPRequest::~HTTPRequest
HTTPRequest::~HTTPRequest() {
    if (mp3cf != 0)
        (*(void(__thiscall**)(void*))((*(void***)mp3cf)[2]))(mp3cf);
    mJobs.destroyRange();
    mStr440.destroy();
    mStr21c.destroy();
    mStr08.destroy();
    *(void**)this = (void*)0x13fb19c;
}

void HTTPRequest::SetMethod(int method) {
    *(int*)((char*)this + 0x2c) = method;
    ((eastl::StrStub*)((char*)this + 8))->assign(HTTPMethodToString(method));
}

// ---------------------------------------------------------------------------
// @ 0x00943D70  add a CellData* to an intrusive vector, bumping its refcount
// ---------------------------------------------------------------------------
struct CellData {
    void* mpVtbl;     // +0
    int   mnRefCount; // +4
};
struct CellPtrVec {
    CellData** mpBegin;     // +0x00
    CellData** mpEnd;       // +0x04
    CellData** mpCapacity;  // +0x08
    void DoInsertValue(CellData**, CellData* const&);   // 0x00A80DD0
};
struct CellHolder {
    char       mPad[0x150];
    CellPtrVec mVec;        // +0x150
    bool AddCell(CellData* p);   // 0x00943D70
};

bool CellHolder::AddCell(CellData* p) {
    if (p != 0) {
        CellData** it = mVec.mpBegin;
        if (it != mVec.mpEnd) {
            do {
                if (*it == p)
                    break;
                ++it;
            } while (it != mVec.mpEnd);
            if (it != mVec.mpEnd)
                return false;
        }
        if (mVec.mpEnd < mVec.mpCapacity) {
            CellData** pEnd = mVec.mpEnd;
            mVec.mpEnd = pEnd + 1;
            if (pEnd != 0)
                *pEnd = p;
        } else {
            mVec.DoInsertValue(mVec.mpEnd, p);
        }
        _InterlockedIncrement((volatile long*)&p->mnRefCount);
        return true;
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x00943BD0  HTTPClient::ParseResponseStatus
// ---------------------------------------------------------------------------
struct WorkerThreadInfo;
__declspec(dllimport) int __cdecl strncmp(const char*, const char*, size_t);
__declspec(dllimport) long __cdecl atol(const char*);

struct HTTPClient {
    char mPad[0x140];
    char* mpReadBuffer;                    // +0x140
    unsigned int mnReadBufferSize;         // +0x144
    int ReadResponseLine(WorkerThreadInfo* wti, char* pBuf, int nMax, char tr);  // 0x009423D0
    int ParseResponseStatus(WorkerThreadInfo* wti);                             // 0x00943BD0
};

struct ReportJob {
    int m00;
    int mResult;            // +0x04
    char mPad[0x24 - 8];
    HTTPRequest* mpRequest; // +0x24
};

int HTTPClient::ParseResponseStatus(WorkerThreadInfo* wti) {
    ReportJob* job = *(ReportJob**)((char*)wti + 0x2c);
    HTTPRequest* req = job->mpRequest;
    req->m43c = 0;

    int n = ReadResponseLine(wti, mpReadBuffer, (int)mnReadBufferSize, 1);
    if (n < 0xe) {
        if (n >= 0)
            job->mResult = 0xd;
        return 0;
    }
    if (strncmp(mpReadBuffer, "HTTP/", 5) != 0 || mpReadBuffer[6] != '.') {
        job->mResult = 0xd;
        return 0;
    }
    int major = mpReadBuffer[5] - '0';
    req->m434 = major;
    int minor = mpReadBuffer[7] - '0';
    req->m438 = minor;
    if (major > 9 || minor > 9) {
        job->mResult = 0xd;
        return 0;
    }
    if (mpReadBuffer[8] != ' ' || mpReadBuffer[0xc] != ' ') {
        job->mResult = 0xd;
        return 0;
    }
    mpReadBuffer[0xc] = 0;
    long code = atol(mpReadBuffer + 9);
    req->m43c = code;
    if (code < 100 || code > 599) {
        req->m43c = 0;
        job->mResult = 0xd;
        return 0;
    }
    if (mnReadBufferSize > (unsigned)n)
        mpReadBuffer[n] = 0;
    else
        mpReadBuffer[mnReadBufferSize - 1] = 0;
    ((eastl::StrStub*)((char*)req + 0x440))->assign(mpReadBuffer + 0xd);
    if (mnReadBufferSize == (unsigned)n) {
        int r;
        do {
            r = ReadResponseLine(wti, mpReadBuffer, (int)mnReadBufferSize, 1);
            if (r < 0)
                return 0;
        } while (mnReadBufferSize == (unsigned)r);
    }
    return 1;
}

// ---------------------------------------------------------------------------
// HTTPClient job-list members (retail layout: mutex +0x60, worker info +0x90, job list head +0x94).
// ---------------------------------------------------------------------------
extern unsigned kTimeoutForever;                  // 0x0143f214 (-1)
extern "C" unsigned long __stdcall GetThreadTime(void);   // 0x0094d340 (jmp thunk)

struct EAMutex {
    unsigned int pad[12];
    int Lock(const unsigned* timeout);            // 0x009221b0 (ret 4)
    int Unlock();                                 // 0x00922270
};

// EA::Thread::Thread handle: one pointer to the refcounted thread data (count at +0x20).
struct ThreadRef {
    void* mpData;
    ThreadRef* Init();                            // 0x00743b50 (this->mpData = 0, returns this)
    void CopyFrom(const ThreadRef* o);            // 0x00922c20 (ret 4; copy + lock xadd +1)
    void Release();                               // 0x00922e10 (lock xadd -1, free at zero)
    int WaitForEnd(const unsigned* timeout, int* status);   // 0x00922940 (ret 8)
};

struct MutexGuard {
    EAMutex* m;
    __forceinline MutexGuard(EAMutex* mm) : m(mm) { m->Lock(&kTimeoutForever); }
    __forceinline ~MutexGuard() { m->Unlock(); }
};

struct SockOptions {
    virtual void o00();
    virtual void o04();
    virtual void o08();
    virtual void o0c();
    virtual void o10();
    virtual void o14();
    virtual void o18();
    virtual void o1c();
    virtual bool IsStream();           // +0x20
    virtual bool IsOpen();             // +0x24
    virtual bool IsReady();            // +0x28
    virtual void o2c();
    virtual void o30();
    virtual void o34();
    virtual void o38();
    virtual void o3c();
    virtual void o40();
    virtual void o44();
    virtual void o48();
    virtual void o4c();
    virtual void o50();
    virtual void o54();
    virtual void o58();
    virtual void o5c();
    virtual void o60();
    virtual void o64();
    virtual void o68();
    virtual void o6c();
    virtual void o70();
    virtual void o74();
    virtual void o78();
    virtual void o7c();
    virtual void o80();
    virtual void o84();
    virtual void o88();
    virtual void o8c();
    virtual void o90();
    virtual void o94();
    virtual void o98();
    virtual void o9c();
    virtual bool GetRecvBuf(unsigned* n);   // +0xa0
    virtual bool SetRecvBuf(unsigned n);    // +0xa4
    virtual bool GetSendBuf(unsigned* n);   // +0xa8
    virtual bool SetSendBuf(unsigned n);    // +0xac
    virtual void ob0();
    virtual void ob4();
    virtual void ob8();
    virtual void obc();
    virtual void oc0();
    virtual void SetSendTimeout(int ms);     // +0xc4
    virtual void oc8();
    virtual void SetRecvTimeout(int ms);     // +0xcc
};
struct QIObj {
    virtual void q00();
    virtual void q04();
    virtual void q08();
    virtual void AddRef();   // +0x0c
    virtual void Release();  // +0x10
    virtual void q14();
    virtual void q18();
    virtual void q1c();
    virtual void q20();
    virtual void q24();
    virtual void SetHost(const char* h);   // +0x28
};
struct SockObj {
    virtual void s00();
    virtual void Release();  // +0x04
    virtual void s08();
    virtual QIObj* QueryInterface(const void* iid);   // +0x0c
    virtual SockOptions* GetOptions();   // +0x10
    virtual void s14();
    virtual void s18();
    virtual void s1c();
    virtual void s20();
    virtual void Connect(void* addr, bool* ok, int flags);   // +0x24
    virtual void s28();
    virtual int GetState();   // +0x2c
};

struct StrRaw {
    char* mpBegin; char* mpEnd; char* mpCapacity; unsigned mAlloc;
    void Assign(const char* first, const char* last);   // 0x00454cb0 (ret 8)
};   // string8 layout, no ctor

struct JobRec {
    unsigned id;
    int      mResult;           // +0x04
    char     pad08[0x1c - 8];
    struct ReqObj* mpRequest;   // +0x1c
};

struct URLObj {
    StrRaw* GetPart(int which);     // 0x0094baf0 (ret 4)
    int     GetScheme();            // 0x0094baa0
    int     GetPort();              // 0x0094a4a0
};
struct ReqObj { char pad[0x30]; URLObj url; };

struct WorkerInfo {
    int    m00;
    char   m04;
    char   m05;
    char   mCancelCurrent;      // +0x06
    char   pad07[5];
    StrRaw msCurrentServer;     // +0x0c
    unsigned short mPort;       // +0x1c
    unsigned short pad1e;
    SockObj* mpSocket;          // +0x20
    int    mProtocol;           // +0x24
    char   mbHaveSocket;        // +0x28
    char   pad29[3];
    JobRec* mpCurrentJob;       // +0x2c
    ThreadRef mThread;          // +0x30
};

struct ListHead { CookieNode* mpNext; CookieNode* mpPrev; };

typedef void (__cdecl *JobNotifyFn)(void* ctx, void* client, unsigned msg, void* job, int extra);

struct NameLookupObj {
    char pad[0x88];
    int Resolve(const char* host);                  // 0x0094d270 (ret 4)
};

struct ReportClient {
    char        pad00[0x24];
    JobNotifyFn mpNotify;       // +0x24
    void*       mpNotifyCtx;    // +0x28
    char        pad2c[0x60 - 0x2c];
    EAMutex     mMutex;         // +0x60
    WorkerInfo* mpWorker;       // +0x90
    ListHead    mJobList;       // +0x94
    char        pad9c[4];
    NameLookupObj mNameLookup;  // +0xa0
    int         mnTimeoutSeconds;   // +0x128
    bool CancelJob(unsigned id);                    // 0x00943910
    bool CancelAllJobs(bool bWait, unsigned timeout);   // 0x00943A30
    bool ConnectToServer(WorkerInfo* wti);          // 0x00942FF0
    void Pump(SockObj* sock);                       // 0x009421B0 (ret 4)
    bool AllocateSocket(URLObj* url, SockObj** out);    // 0x00941F90 (ret 8)
};


// Unlink the node before `next` (eastl::list::erase does ++position first), free its two
// refcounted payload pointers and the node.
static __forceinline void EraseBefore(CookieNode* pos) {
    CookieNode* n = pos->mpPrev;
    n->mpPrev->mpNext = n->mpNext;
    n->mpNext->mpPrev = n->mpPrev;
    if (n->mData.mp24) n->mData.mp24->Release();
    if (n->mData.mp1c) n->mData.mp1c->Release();
    operator_delete__(n);
}

// @ 0x00943910  EA::Internet::HTTPClient::CancelJob(unsigned id)
bool ReportClient::CancelJob(unsigned id) {
    mMutex.Lock(&kTimeoutForever);
    for (CookieNode* n = mJobList.mpNext; n != (CookieNode*)&mJobList; n = n->mpNext) {
        Cookie40* job = &n->mData;
        if ((unsigned)job->m00[0] == id) {
            job->m00[1] = 8;
            if (mpNotify)
                mpNotify(mpNotifyCtx, this, 0x700af301, job, 0);
            n = n->mpNext;
            EraseBefore(n);
            mMutex.Unlock();
            return true;
        }
    }
    WorkerInfo* w = mpWorker;
    if (w && w->mpCurrentJob && w->mpCurrentJob->id == id) {
        w->mCancelCurrent = 1;
        mMutex.Unlock();
        return true;
    }
    mMutex.Unlock();
    return false;
}

// @ 0x00943A30  HTTPClient::CancelAllJobs(bool bWait, unsigned timeout): cancel every queued job, flag the running one
bool ReportClient::CancelAllJobs(bool bWait, unsigned timeout) {
    ThreadRef thread;
    thread.Init();
    bool haveThread = false;
    mMutex.Lock(&kTimeoutForever);
    if (bWait && mpWorker) {
        thread.CopyFrom(&mpWorker->mThread);
        haveThread = true;
    }
    CookieNode* head = (CookieNode*)&mJobList;
    CookieNode* n = head->mpNext;
    if (n != head) {
        do {
            Cookie40* job = &n->mData;
            job->m00[1] = 8;
            if (mpNotify)
                mpNotify(mpNotifyCtx, this, 0x700af301, job, 0);
            CookieNode* next = n->mpNext;
            EraseBefore(next);
            n = next;
        } while (n != head);
    }
    ListDestroy(head);
    head->mpNext = head;
    head->mpPrev = head;
    EAMutex* m = &mMutex;
    m->Lock(&kTimeoutForever);
    WorkerInfo* w = mpWorker;
    if (w)
        w->mCancelCurrent = 1;
    m->Unlock();
    m->Unlock();
    if (haveThread) {
        bool ok;
        if (timeout) {
            unsigned deadline = GetThreadTime() + timeout;
            ok = thread.WaitForEnd(&deadline, 0) == 2;
        } else {
            ok = thread.WaitForEnd(&kTimeoutForever, 0) == 2;
        }
        thread.Release();
        return ok;
    }
    thread.Release();
    return true;
}

// ---------------------------------------------------------------------------
// 0x00942FF0  EA::Internet::HTTPClient::ConnectToServer(WorkerThreadInfo*)
// Resolve the current job's URL host, (re)use or allocate the socket, tune its buffers and connect.
// ---------------------------------------------------------------------------
extern "C" __declspec(dllimport) int __cdecl _stricmp(const char*, const char*);
extern char gEmptyBuf[];                                    // 0x01667bac
extern const char kEastlName2[];                            // "EASTL" (0x013f2150)
extern char kIID_SockQI[];                                  // 0x0164c507
bool __cdecl IsIPAddressString(const char* s);              // 0x0094c190
unsigned __cdecl ParseIPAddress(const char* s);             // 0x0094c130
void* __cdecl MemMoveS(void* dst, const void* src, unsigned n);   // 0x011e0744
struct SrvString {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    __forceinline SrvString(const char* first, const char* last) {
        unsigned n = last - first;
        if (n + 1 > 1) {
            mpBegin = (char*)operator_new(n + 1, "EASTL", 0, 0, kEastlFile, 0xd1);
            mpCapacity = mpBegin + n + 1;
        } else {
            mpBegin = gEmptyBuf; mpCapacity = gEmptyBuf + 1;
        }
        MemMoveS(mpBegin, first, n);
        mpEnd = mpBegin + (last - first);
        *mpEnd = 0;
    }
    __forceinline ~SrvString() {
        if ((mpCapacity - mpBegin) > 1 && mpBegin) operator_delete__(mpBegin);
    }
};
struct SockAddrIn { unsigned short family; unsigned short port; unsigned addr; };

// @ 0x00942FF0
bool ReportClient::ConnectToServer(WorkerInfo* wti) {
    unsigned cur, want;
    bool ok;
    JobRec* job = wti->mpCurrentJob;
    SockAddrIn sa;
    sa.family = 2; sa.port = 0; sa.addr = 0;
    URLObj* url = &job->mpRequest->url;
    StrRaw* part = url->GetPart(3);
    SrvString host(part->mpBegin, part->mpEnd);
    unsigned short port = (unsigned short)url->GetPort();
    URLObj* u2 = &job->mpRequest->url;
    int proto;
    if (u2->GetScheme() == 3)
        proto = 2;
    else if (u2->GetScheme() == 2 || u2->GetPort() != 0x1bb)
        proto = 1;
    else
        proto = 2;
    SockObj** pSock = &wti->mpSocket;
    if (wti->mbHaveSocket && *pSock) {
        if ((*pSock)->GetOptions()->IsStream()
            && wti->mpSocket->GetState() == 2
            && wti->mProtocol == proto
            && port == wti->mPort
            && _stricmp(host.mpBegin, wti->msCurrentServer.mpBegin) == 0)
            goto success;
    }
    Pump(wti->mpSocket);
    if (!*pSock || wti->mProtocol != proto) {
        if (*pSock) {
            SockObj* old = *pSock;
            *pSock = 0;
            old->Release();
        }
        if (!AllocateSocket(&job->mpRequest->url, pSock)) {
            job->mResult = 2;
            goto fail;
        }
    }
    unsigned ip;
    if (IsIPAddressString(host.mpBegin)) {
        ip = ParseIPAddress(host.mpBegin);
    } else {
        ip = mNameLookup.Resolve(host.mpBegin);
        if (!ip) {
            job->mResult = 4;
            goto fail;
        }
    }
    sa.addr = ip;
    if ((StrRaw*)&host != &wti->msCurrentServer)
        wti->msCurrentServer.Assign(host.mpBegin, host.mpEnd);
    wti->mPort = port;
    wti->mProtocol = proto;
    if (port)
        sa.port = _byteswap_ushort(port);
    else
        sa.port = (proto == 2) ? 0xbb01 : 0x5000;
    QIObj* qi = (*pSock)->QueryInterface(kIID_SockQI);
    if (qi) {
        qi->AddRef();
        qi->SetHost(host.mpBegin);
    }
    ok = false;
    if ((*pSock)->GetOptions()->IsOpen()) {
        cur = 0x4000; want = 0x20000;
        if (!(*pSock)->GetOptions()->GetRecvBuf(&cur)) cur = want;
        if (cur <= want) {
            do {
                if ((*pSock)->GetOptions()->SetRecvBuf(want)) break;
                want >>= 1;
            } while (want >= cur);
        }
        cur = 0x4000; want = 0x8000;
        if (!(*pSock)->GetOptions()->GetSendBuf(&cur)) cur = want;
        if (cur <= want) {
            do {
                if ((*pSock)->GetOptions()->SetSendBuf(want)) break;
                want >>= 1;
            } while (want >= cur);
        }
        if (mnTimeoutSeconds != -1) {
            (*pSock)->GetOptions()->SetRecvTimeout(mnTimeoutSeconds * 1000);
            (*pSock)->GetOptions()->SetSendTimeout(mnTimeoutSeconds * 1000);
        }
        if ((*pSock)->GetOptions()->IsReady())
            (*pSock)->Connect(&sa, &ok, 0);
    }
    if (ok) {
        if (qi) qi->Release();
        goto success;
    }
    job->mResult = 5;
    if (qi) qi->Release();
fail:
    return false;
success:
    return true;
}
