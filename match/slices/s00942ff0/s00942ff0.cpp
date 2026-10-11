// Batch "gold1" slice s00942ff0 - EA::Internet::HTTPClient Job/WorkerThreadInfo helpers.
// Reconstructed from the original disassembly + Ghidra decompiles (cards in work/match).
// Flags: /O2 /MD /Gy /TP /GS-
#include <intrin.h>
#include <new>
#include "types.h"

// ---------------------------------------------------------------------------
// External helpers / callees (defined elsewhere in the image).
// ---------------------------------------------------------------------------
extern "C" void __cdecl operator_delete__(void* p);
void* __cdecl operator_new(unsigned int size, const char* name, int a, int b,
                           const char* file, int line);
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
// @ 0x00942FF0  (partial: see partial.txt) - request formatting, not reconstructed
// ---------------------------------------------------------------------------
int FUN_00942ff0(int param_1) {
    (void)param_1;
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x00943910  (partial: see partial.txt) - Report::HandleHTTPResponse, not reconstructed
// ---------------------------------------------------------------------------
void FUN_00943910(void* self, int param) {
    (void)self;
    (void)param;
}

// ---------------------------------------------------------------------------
// @ 0x00943A30  (partial: see partial.txt) - Report state machine, not reconstructed
// ---------------------------------------------------------------------------
void FUN_00943a30(void* self, int param) {
    (void)self;
    (void)param;
}
