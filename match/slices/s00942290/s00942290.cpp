// Slice s00942290 -- EA::Internet (UTFInternet): HTTPClient response reader core
// (raw/line/chunked/body), worker-job progress notification, refcounted log-cookie
// helpers and small URL / user-agent setters.
// Module flags: /O2 /MD /Gy /TP /GS-
#include "types.h"
#include <intrin.h>

// ---------------------------------------------------------------------------
// External CRT / engine helpers (addresses noted; relocations are masked by the
// byte comparison, so plain declarations are enough).
// ---------------------------------------------------------------------------
void* __cdecl operator new(unsigned int, const char*, int, int, const char*, int);  // 0x00F473A0
void  __cdecl operator_delete__(void*) throw();                                     // 0x00F47380
void* __cdecl memmove(void*, const void*, unsigned int);                            // 0x011E0744
extern "C" int __cdecl strncmp(const char*, const char*, unsigned int);
extern "C" __declspec(dllimport) int __cdecl isxdigit(int);
extern "C" unsigned int __cdecl strlen(const char*);

// 0x00941BB0
int __cdecl GetTime64();
// 0x00941C40
const char* __cdecl HeaderFieldToFieldString(int field);
// 0x0092D6B0 -- string -> 64-bit integer (strtoll-like)
__int64 __cdecl ParseInt64(const char* s, int, int);

// ---------------------------------------------------------------------------
// Vtable helpers (__thiscall is only legal in function-pointer typedefs).
// ---------------------------------------------------------------------------
typedef void (__thiscall *VFV)(void*);
typedef void (__thiscall *VFV2)(void*, void*, unsigned);
typedef int  (__thiscall *VFI)(void*);
typedef int  (__thiscall *VFI1)(void*, int);
typedef int  (__thiscall *VFI0)(void*);
typedef char (__thiscall *VFC1)(void*, int);
typedef char (__thiscall *VFC2)(void*, void*, int);
typedef int  (__thiscall *VFI3)(void*, void*, unsigned, int);
#define VSLOT(p, off) ((*(void***)(p))[(off) / 4])
#define VC0(p, off)   ((VFI)VSLOT(p, off))(p)
#define VC3(p, off, a, b, c) ((VFI3)VSLOT(p, off))(p, (void*)(a), (unsigned)(b), (int)(c))

// ---------------------------------------------------------------------------
// Types
// ---------------------------------------------------------------------------
namespace eastl {
// eastl::basic_string<char>: begin/end/capacity inline (stateless allocator + pad).
struct StrStub {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    int   mAllocPad;
    void assign(const char* first, const char* last);        // 0x00454CB0
    void assignRange(const char* first, const char* last);   // 0x00942E50 (this slice)
};
// eastl::fixed_string<char,N>-style buffer: just the assign entry point we call.
struct FixedStub {
    char data[0x100];
    void assign(const char* first, const char* last);        // 0x0060A2C0
};
}

// Refcounted COM object: vtable slot 0 is the (deleting) destructor, count at +4.
struct RefObj {
    virtual void Destroy(int flags);
    int mnRefCount;
    void AddRef() {
        _InterlockedIncrement((volatile long*)&mnRefCount);
    }
    int Release() {
        return _InterlockedDecrement((volatile long*)&mnRefCount);
    }
};

namespace EA { namespace Internet {

// HTTPClient::WorkerThreadInfo (0x34).
struct WorkerThreadInfo {
    void* mpOwner;                        // +0x00
    char  mbCreated;                      // +0x04
    char  mbShouldQuit;                   // +0x05
    char  mbCancelCurrent;                // +0x06
    char  pad07;
    int   mnShouldPauseCount;             // +0x08
    char  msCurrentServer[0x1c - 0x0c];   // +0x0c (string)
    unsigned short mnCurrentPort;         // +0x1c
    char  pad1e[2];
    void* mpSocket;                       // +0x20 (AutoRefCount<IStreamSocket>)
    int   mCurrentProtocol;               // +0x24
    char  mbServerIsV11;                  // +0x28
    char  pad29[0x2c - 0x29];
    void* mpCurrentJob;                   // +0x2c
};

// HTTPClient::Job (binary layout).
struct Job {
    unsigned int mId;                     // +0x00
    int   mResult;                        // +0x04
    int   mStartTimeSeconds;              // +0x08
    int   mTimeoutTimeSeconds;            // +0x0c
    unsigned int mnTryCount;              // +0x10
    unsigned int mPercentComplete;        // +0x14
    unsigned int mnRedirectionCount;      // +0x18
    void* mpRequest;                      // +0x1c
    char  pad20[0x24 - 0x20];
    void* mpResponse;                     // +0x24
    char  pad28[0x30 - 0x28];
    unsigned __int64 mnLastNotifySize;    // +0x30
};

class HTTPClient {
public:
    char  pad00[0x24];
    void* mpNotify;                       // +0x24 (NotifyFn)
    void* mpNotifyCtx;                    // +0x28
    char  pad2c[0x30 - 0x2c];
    int   mnLoggingEnabled;               // +0x30
    char  pad34[0x54 - 0x34];
    void* mpReadLogStream;                // +0x54
    void* mpWriteLogStream;               // +0x58
    char  pad5c[0x90 - 0x5c];
    WorkerThreadInfo* mpWorkerThreadInfo; // +0x90
    char  pad94[0x130 - 0x94];
    unsigned __int64 mnBytesSent;         // +0x130
    unsigned __int64 mnBytesReceived;     // +0x138
    char* mpReadBuffer;                   // +0x140
    unsigned int mnReadBufferSize;        // +0x144
    char* mpWriteBuffer;                  // +0x148
    unsigned int mnWriteBufferSize;       // +0x14c

    bool  ReadRawBody(WorkerThreadInfo* wti, char* pBuf);                          // 00942290
    int   ReadResponseLine(WorkerThreadInfo* wti, char* pBuf, int nMax, char tr);  // 009423D0
    bool  DoJobUpdate(int job, unsigned doneLo, unsigned doneHi,
                      unsigned totalLo, int totalHi, unsigned* progress);          // 00942530
    __int64 ReadResponseData(WorkerThreadInfo* wti, unsigned totalLo,
                             unsigned totalHi, char notify);                        // 00942690
    __int64 ReadChunkedResponseData(WorkerThreadInfo* wti);                         // 009428B0
    bool  ReadResponseBody(WorkerThreadInfo* wti);                                 // 00942B40
    void  __declspec(noinline) SetUserAgent(const char* p);                        // 00942FB0
};

}} // namespace EA::Internet

using namespace EA::Internet;

// ---------------------------------------------------------------------------
// Cookie40 (0x40): two refcounted members at +0x1c and +0x24. The copy
// constructor, copy assignment and destructor are all compiler-generated from
// the member list (and must therefore match the original byte-for-byte).
// ---------------------------------------------------------------------------
template<class T>
struct AutoRefCount {
    T* mpObject;
    AutoRefCount() : mpObject(0) {}
    AutoRefCount(const AutoRefCount& o) {
        mpObject = o.mpObject;
        if (mpObject) ((RefObj*)mpObject)->AddRef();
    }
    __forceinline AutoRefCount& operator=(const AutoRefCount& o) {
        Assign(o.mpObject);
        return *this;
    }
    ~AutoRefCount() {
        Release();
    }
    void Release() {
        RefObj* p = (RefObj*)mpObject;
        if (p) {
            int rc = p->Release();
            if (rc == 0) {
                _InterlockedExchange((volatile long*)&p->mnRefCount, 1);
                if (p)
                    p->Destroy(1);
            }
        }
    }
    void Assign(T* p) {
        T* old = mpObject;
        if (p != old) {
            if (p) ((RefObj*)p)->AddRef();
            mpObject = p;
            if (old) {
                int rc = old->Release();
                if (rc == 0) {
                    _InterlockedExchange((volatile long*)&old->mnRefCount, 1);
                    if (old)
                        old->Destroy(1);
                }
            }
        }
    }
};

struct Cookie40 {
    int   m00, m04, m08, m0c, m10, m14, m18;   // +0x00
    AutoRefCount<RefObj> mp1c;                 // +0x1c
    bool  m20;                                 // +0x20
    AutoRefCount<RefObj> mp24;                 // +0x24
    int   m28;                                 // +0x28
    // +0x2c padding: m30 is 8-byte aligned.
    unsigned __int64 m30;                      // +0x30
    unsigned __int64 m38;                      // +0x38
    ~Cookie40();
};

// Out-of-line so the destructor is emitted as its own symbol (0x00942630). The
// member destructors still run automatically, in reverse declaration order.
Cookie40::~Cookie40() {}

static int StrLen(const char* s) {
    const char* p = s;
    char c = *p;
    while (c) { ++p; c = *p; }
    return (int)(p - s);
}

// ---------------------------------------------------------------------------
// @ 0x00942290  HTTPClient::ReadRawBody
// ---------------------------------------------------------------------------
bool HTTPClient::ReadRawBody(WorkerThreadInfo* wti, char* pBuf) {
    int remaining = StrLen(pBuf);
    unsigned consumed = 0;
    while (remaining != 0 && wti->mbCancelCurrent == 0 && wti->mbShouldQuit == 0) {
        Job* job = (Job*)wti->mpCurrentJob;
        if (job->mTimeoutTimeSeconds > 0) {
            int now = GetTime64();
            if (job->mTimeoutTimeSeconds < now) { job->mResult = 6; return false; }
            if (consumed > 0) {
                job->mTimeoutTimeSeconds = job->mStartTimeSeconds + now;
                consumed = 0;
            }
        }
        void* sock = wti->mpSocket;
        void* s2 = (void*)((VFI)VSLOT(sock, 0x10))(sock);
        char r = ((VFC1)VSLOT(s2, 0x68))(s2, 1000);
        if (r != 0 || (VC0(sock, 0x2c) != 2)) {
            char* dst = pBuf + consumed;
            int n = VC3(sock, 0x48, dst, remaining, 0);
            if (n < 0) { job->mResult = 7; return false; }
            unsigned nWrite = (unsigned)n;
            if (n == -1)
                nWrite = (unsigned)StrLen(dst);
            if (mnLoggingEnabled > 0)
                ((VFV2)VSLOT(mpWriteLogStream, 0x38))(mpWriteLogStream, dst, nWrite);
            consumed += (unsigned)n;
            remaining -= n;
            mnBytesSent += (unsigned __int64)(__int64)n;
        }
    }
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x009423D0  HTTPClient::ReadResponseLine
// ---------------------------------------------------------------------------
int HTTPClient::ReadResponseLine(WorkerThreadInfo* wti, char* pBuf, int nMax, char trim) {
    if (pBuf == 0 || nMax < 1) { ((Job*)wti->mpCurrentJob)->mResult = 3; return -1; }
    int nReadOK = 0;
    int i = 0;
    char* p = pBuf;
    for (;;) {
        Job* job = (Job*)wti->mpCurrentJob;
        if (job->mTimeoutTimeSeconds > 0) {
            int now = GetTime64();
            if (job->mTimeoutTimeSeconds < now) { job->mResult = 6; return -1; }
            if (nReadOK > 0) { job->mTimeoutTimeSeconds = job->mStartTimeSeconds + now; nReadOK = 0; }
        }
        void* sock = wti->mpSocket;
        bool doRead = (wti->mCurrentProtocol == 2);
        if (!doRead) {
            void* s2 = (void*)((VFI)VSLOT(sock, 0x10))(sock);
            int r = ((VFI1)VSLOT(s2, 100))(s2, 1000);
            if (r != 0) doRead = true;
        }
        if (doRead) {
            nReadOK = VC3(sock, 0x44, p, 1, 0);
            if (nReadOK < 1) { job->mResult = 7; return nReadOK; }
            if (mnLoggingEnabled > 0)
                ((VFV2)VSLOT(mpReadLogStream, 0x38))(mpReadLogStream, p, 1);
            unsigned old = (unsigned)mnBytesReceived;
            mnBytesReceived += 1;
            *(unsigned*)((char*)&mnBytesReceived + 4) += (old > 0xfffffffeu);
            if (*p == '\n') {
                if (trim != 0) {
                    if (i > 0 && pBuf[i - 1] == '\r') --i;
                    pBuf[i] = '\0';
                    return i;
                }
                return i + 1;
            }
            ++i; ++p;
        }
        if (nMax <= i) return i;
    }
}

// ---------------------------------------------------------------------------
// @ 0x00942530  HTTPClient::DoJobUpdate
// ---------------------------------------------------------------------------
bool HTTPClient::DoJobUpdate(int job, unsigned doneLo, unsigned doneHi,
                             unsigned totalLo, int totalHi, unsigned* progress) {
    void (*notify)(void*, void*, unsigned, void*, void*) =
        (void (*)(void*, void*, unsigned, void*, void*))mpNotify;
    if (notify == 0) return false;
    if (totalHi < 0) return false;
    if (totalHi < 1 && totalLo < 0x801) return false;

    unsigned __int64 newVal;
    if (totalLo == 0xffffffffu && totalHi == 0x7fffffff) {
        newVal = 0;
    } else if (totalLo == 0 && totalHi == 0) {
        newVal = 0x32;
    } else {
        unsigned __int64 done  = (unsigned __int64)doneLo | ((unsigned __int64)doneHi << 32);
        unsigned __int64 total = (unsigned __int64)totalLo | ((unsigned __int64)(unsigned)totalHi << 32);
        unsigned __int64 q = (done * 100) / total;
        newVal = q;
        if ((q >> 32) != 0 || (unsigned)q > 100) newVal = 100;
    }
    unsigned __int64 prev = (unsigned __int64)progress[0] |
                            ((unsigned __int64)progress[1] << 32);
    unsigned __int64 sub = newVal - prev;
    if ((unsigned)(sub >> 32) == 0 && (unsigned)sub < 10) return false;

    (void)job;
    notify(mpNotifyCtx, this, 0x700af300, &doneHi, progress);
    progress[0] = (unsigned)newVal;
    progress[1] = (unsigned)(newVal >> 32);
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x00942690  HTTPClient::ReadResponseData
// ---------------------------------------------------------------------------
__int64 HTTPClient::ReadResponseData(WorkerThreadInfo* wti, unsigned totalLo,
                                     unsigned totalHi, char notify) {
    __int64 remain = ((__int64)(int)totalHi << 32) | (unsigned)totalLo;
    __int64 done = 0;
    unsigned prog = 0;
    int prevN = 0;
    for (;;) {
        if (remain == 0 ||
            wti->mbCancelCurrent != 0 || wti->mbShouldQuit != 0)
            break;
        Job* job = (Job*)wti->mpCurrentJob;
        if (job->mTimeoutTimeSeconds > 0) {
            int now = GetTime64();
            if (job->mTimeoutTimeSeconds < now) { job->mResult = 6; done = -1; break; }
            // Rolling deadline: a read that produced data restarts the timeout window.
            if (prevN > 0) { job->mTimeoutTimeSeconds = job->mStartTimeSeconds + now; prevN = 0; }
        }
        bool doRead = (wti->mCurrentProtocol == 2);
        if (!doRead) {
            void* s2 = (void*)((VFI)VSLOT(wti->mpSocket, 0x10))(wti->mpSocket);
            if (((VFC1)VSLOT(s2, 100))(s2, 1000) != 0) {
                doRead = true;
            } else {
                if (VC0(wti->mpSocket, 0x2c) != 2) { job->mResult = 7; done = -1; break; }
                continue;
            }
        }
        // Never ask for more than is still outstanding; `remain` may be negative for an
        // unbounded request, in which case the whole read buffer is requested.
        unsigned size = mnReadBufferSize;
        if (remain < (__int64)size) size = (unsigned)remain;
        unsigned n = (unsigned)VC3(wti->mpSocket, 0x44, mpReadBuffer, size, 0);
        prevN = (int)n;
        if ((int)n < 1) {
            done = (__int64)(int)n;
            if (!(totalLo == 0xffffffffu && totalHi == 0x7fffffff)) {
                job->mResult = 2;
                Job* jb = (Job*)wti->mpCurrentJob;
                jb->mnLastNotifySize = (unsigned __int64)done;
            }
            break;
        }
        mnBytesReceived += n;
        // When the socket returned -1 the log line is the partial buffer contents, so its
        // length is strlen(mpReadBuffer); otherwise it is the raw byte count.
        unsigned logLen = n;
        if ((int)n == -1) logLen = (unsigned)StrLen(mpReadBuffer);
        if (mnLoggingEnabled > 0)
            ((VFV2)VSLOT(mpReadLogStream, 0x38))(mpReadLogStream, mpReadBuffer, logLen);
        void* filt = *(void**)((char*)job->mpResponse + 0xf3c);
        if (!((VFC2)VSLOT(filt, 0x38))(filt, mpReadBuffer, (int)n)) {
            job->mResult = 0xb; done = -1; break;
        }
        done += (__int64)(int)n;
        remain -= (__int64)(int)n;
        if (notify != 0)
            DoJobUpdate((int)job, (unsigned)done, (unsigned)((unsigned __int64)done >> 32),
                        totalLo, totalHi, &prog);
    }
    Job* jb = (Job*)wti->mpCurrentJob;
    jb->mnLastNotifySize = (unsigned __int64)done;
    return done;
}

// 0x00942050 / 0x009420E0 are members of the *response* object that the HTTPClient
// job holds; ReadResponseBody calls them with `this = job->mpResponse + 0x4a4`.
struct HTTPResponseHdr {
    bool FindHeader(const char* name, void** out, int index);       // 00942050
    bool FindHeaderByField(int field, void** out, int index);       // 009420E0
};

// ---------------------------------------------------------------------------
// @ 0x00942B40  HTTPClient::ReadResponseBody
// ---------------------------------------------------------------------------
bool HTTPClient::ReadResponseBody(WorkerThreadInfo* wti) {
    Job* job = (Job*)wti->mpCurrentJob;
    if (*(int*)((char*)job->mpRequest + 0x2c) == 3) return true;
    if (*(int*)((char*)job->mpResponse + 0xf3c) == 0) { job->mResult = 0xb; return false; }

    __int64 len = 0;
    bool chunked = false;
    void* outptr[2];
    HTTPResponseHdr* hdr = (HTTPResponseHdr*)((char*)job->mpResponse + 0x4a4);
    const char* f = HeaderFieldToFieldString(0x26);
    char found = (char)hdr->FindHeader(f, (void**)outptr, 0);
    if (found == 0 || (len = ParseInt64((const char*)outptr[0], 0, 10), len != 0)) {
        const char* f2 = HeaderFieldToFieldString(5);
        char found2 = (char)hdr->FindHeader(f2, (void**)outptr, 0);
        if (found2 != 0) {
            const char* a = (const char*)outptr[0];
            const char* b = "chunked";
            while (*a != 0 && *a == *b) { ++a; ++b; if (*a == 0) break; }
            if (*a == *b) chunked = true;
        }
        if (len == 0 && !chunked) {
            void* req = job->mpRequest;
            int code = *(int*)((char*)job->mpResponse + 0x43c);
            char found3 = (char)hdr->FindHeaderByField(2, (void**)outptr, 0);
            if (found3 != 0 && strncmp((const char*)outptr[0], "close", 5) != 0) return true;
            int proto = *(int*)((char*)req + 0x2c);
            if (proto != 2 && proto != 4) return true;
            if ((unsigned)(code - 200) > 99) return true;
            len = 0x7fffffffffffffffLL;
        }
        job = (Job*)wti->mpCurrentJob;
        job->mnLastNotifySize = 0;
        __int64 r;
        if (chunked) r = ReadChunkedResponseData(wti);
        else        r = ReadResponseData(wti, (unsigned)len, (unsigned)(len >> 32), 1);
        if (wti->mbCancelCurrent == 0 && wti->mbShouldQuit == 0 && r < 0) return false;
    }
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x009428B0  HTTPClient::ReadChunkedResponseData
// ---------------------------------------------------------------------------
__int64 HTTPClient::ReadChunkedResponseData(WorkerThreadInfo* wti) {
    __int64 total = 0;
    for (;;) {
        __int64 n = ReadResponseLine(wti, mpReadBuffer, mnReadBufferSize, 0);
        if (n < 0) { total = n; break; }
        // scan the hex digits of the chunk-size line
        __int64 i;
        for (i = 0; i < n && isxdigit(mpReadBuffer[i]); ++i) {}
        if (i <= 0 || i == n) {
            ((Job*)wti->mpCurrentJob)->mResult = 0xd;
            total = -1;
            break;
        }
        mpReadBuffer[i] = 0;
        __int64 chunk = ParseInt64(mpReadBuffer, 0, 16);
        if (n == (__int64)(int)mnReadBufferSize) {
            // the size line filled the buffer: drain the rest of the line
            while (mpReadBuffer[mnReadBufferSize - 1] != '\n') {
                __int64 r = ReadResponseLine(wti, mpReadBuffer, mnReadBufferSize, 0);
                if (r < 0) { total = r; break; }
                if (r != (__int64)(int)mnReadBufferSize) break;
            }
        }
        __int64 got = ReadResponseData(wti, (unsigned)chunk, (unsigned)(chunk >> 32), 0);
        if (got < chunk) { total = got; break; }
        total += got;
        if (chunk == 0) {
            // last chunk: consume the trailer lines
            for (;;) {
                __int64 r = ReadResponseLine(wti, mpReadBuffer, mnReadBufferSize, 1);
                if (r < 0) { total = r; break; }
                bool full = (r == (__int64)(int)mnReadBufferSize);
                if (r == 0 || full) break;
            }
            break;
        }
        // CRLF that terminates the chunk data
        __int64 t = ReadResponseLine(wti, mpReadBuffer, mnReadBufferSize, 0);
        if (t < 0) { total = t; break; }
        if (t < 1 || t > 2) {
            ((Job*)wti->mpCurrentJob)->mResult = 0xd;
            total = -1;
            break;
        }
        if (wti->mbCancelCurrent != 0 || wti->mbShouldQuit != 0) break;
    }
    ((Job*)wti->mpCurrentJob)->mnLastNotifySize = (unsigned __int64)total;
    return total;
}

// ---------------------------------------------------------------------------
// @ 0x00942CE0  Cookie40 copy constructor   (implicit)
// @ 0x00942D70  Cookie40 copy assignment    (implicit)
// @ 0x00942630  Cookie40 destructor         (implicit)
// ---------------------------------------------------------------------------

// ---------------------------------------------------------------------------
// @ 0x00942E50  eastl string assign(first, last)
// ---------------------------------------------------------------------------
void eastl::StrStub::assignRange(const char* first, const char* last) {
    if (first == last) return;
    unsigned len = (unsigned)(last - first);
    unsigned cap = (unsigned)(mpCapacity - mpBegin) - 1;
    unsigned need = (unsigned)(mpEnd - mpBegin) + len;
    if (cap < need) {
        unsigned newcap = (cap < 9) ? 8 : cap * 2;
        if (need > newcap) newcap = need;
        char* p = (char*)operator new(newcap + 1,
                     "EASTL", 0, 0,
                     "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h",
                     0xd1);
        memmove(p, mpBegin, (unsigned)(mpEnd - mpBegin));
        char* dst = p + (mpEnd - mpBegin);
        memmove(dst, first, len);
        dst[len] = 0;
        if (cap > 1 && mpBegin != 0)
            operator_delete__(mpBegin);
        mpBegin = p;
        mpEnd = dst + len;
        mpCapacity = p + newcap + 1;
    } else {
        memmove(mpEnd + 1, first + 1, (unsigned)(last - (first + 1)));
        mpEnd[len] = 0;
        *mpEnd = *first;
        mpEnd += len;
    }
}

// ---------------------------------------------------------------------------
// @ 0x00942F70  set the request URL and copy the "political id"
// ---------------------------------------------------------------------------
// A URL object: only its two call entry points are needed here.
struct URLClass {
    char data[0x90];
    void  SetURL(const char* url, int force);   // 0x0094A6A0
    void* GetAccessor();                         // 0x0097E850
};
struct UrlHolder {
    char pad0[0x30];
    URLClass mUrl;              // +0x30 .. +0xc0
    char padc0[0x20];
    eastl::FixedStub mString;   // +0xe0
    void  SetURL(const char* url);
};

void UrlHolder::SetURL(const char* url) {
    mUrl.SetURL(url, 1);
    void* p1 = mUrl.GetAccessor();
    int v1 = *(int*)((char*)p1 + 4);
    void* p2 = mUrl.GetAccessor();
    int v2 = *(int*)p2;
    mString.assign((const char*)v2, (const char*)v1);
}

// ---------------------------------------------------------------------------
// @ 0x00942FB0  HTTPClient::SetUserAgent
// ---------------------------------------------------------------------------
void HTTPClient::SetUserAgent(const char* p) {
    if (p) {
        const char* end = p + strlen(p);
        ((eastl::StrStub*)((char*)this + 0x14))->assign(p, end);
    } else {
        eastl::StrStub* ua = (eastl::StrStub*)((char*)this + 0x14);
        if (ua->mpBegin != ua->mpEnd) {
            *ua->mpBegin = 0;
            ua->mpEnd = ua->mpBegin;
        }
    }
}

// ---------------------------------------------------------------------------
// Keep every reconstructed body emitted (referenced through a dummy function).
// ---------------------------------------------------------------------------
void __declspec(noinline) SliceEmitAnchors(HTTPClient* c, WorkerThreadInfo* w,
                                           Cookie40* ck, const Cookie40* cs,
                                           eastl::StrStub* ss, UrlHolder* uh,
                                           const char* s, char* b) {
    c->ReadRawBody(w, b);
    c->ReadResponseLine(w, b, 1, 0);
    {
        unsigned p = 0;
        c->DoJobUpdate(0, 0, 0, 0x1000, 0, &p);
    }
    c->ReadResponseData(w, 0, 0, 0);
    c->ReadChunkedResponseData(w);
    c->ReadResponseBody(w);
    c->SetUserAgent(s);
    {
        Cookie40 tmp(*cs);   // 00942CE0: copy constructor
        *ck = tmp;           // 00942D70: copy assignment
        ck->~Cookie40();     // 00942630: destructor
    }
    ss->assignRange(s, s);
    uh->SetURL(s);
}
