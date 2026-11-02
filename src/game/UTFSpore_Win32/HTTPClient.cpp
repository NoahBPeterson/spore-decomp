// src/game/UTFSpore_Win32/HTTPClient.cpp -- migrated from slice(s) s00944f40, s00943f60, s00945ed0, s00942ff0, s00942290, s009413d0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/HTTPClient.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Internet/HTTPClient.h"
#include <intrin.h>
#include <new>
#include "EA/Internet/HTTPResponse.h"
#include "EA/IO/FileStream.h"
#include "EA/IO/IStream.h"
#include "EA/Thread/Mutex.h"
#include "EA/Thread/Thread.h"
#include "EA/Internet/IRequestResponseFilter.h"
#include "EA/Internet/HTTPFormURLEncodedPostBodyStream.h"
#include "EA/Internet/HTTPMultipartFormDataPostBodyStream.h"
#include "EA/Internet/HTTPMultipartRelatedPostBodyStream.h"
#include "EA/Internet/HTTPRequest.h"
#include "EA/Internet/URL.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) __int64 __cdecl _time64(__int64*);
extern "C" __declspec(dllimport) int __cdecl _stricmp(const char*, const char*);

// ---- items of slice s009413d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" void* FUN_0094F0D0();      // 0x0094F0D0
extern "C" void* FUN_0094CD40();      // 0x0094CD40
extern "C" unsigned int __cdecl strlen(const char*);
void* __cdecl operator_new_6(unsigned int, const char*, int, int, int, int);
struct HTTPClient {
    bool AllocBuffer();
    bool FindHeader(char* name, void* out, int index);
    bool FindHeaderByField(int field, void* out, int index);
    void SetNotificationTarget(void* target, void* ctx);
    int  SendCallback(const char* data, int len);
    void Pump(int* stream);
};
struct SockMgr {
    int   __thiscall FUN_0094BAA0();  // 0x0094BAA0 (this = caller's first dword)
    void* __thiscall FUN_0094F030();  // 0x0094F030 SSLManager::CreateStreamSocket
};
// ---- items of slice s009413d0 end

// ---- items of slice s00942290 begin (TODO(rewrite): local stubs, replace by canonical classes)
__declspec(dllimport) int __cdecl strncmp(const char*, const char*, size_t);
extern "C" __declspec(dllimport) void* __cdecl memmove(void*, const void*, unsigned int);
extern "C" __declspec(dllimport) int __cdecl isxdigit(int);
void* __cdecl operator new(unsigned int, const char*, int, int, const char*, int);  // 0x00F473A0
void  __cdecl operator_delete__(void*) throw();                                     // 0x00F47380
void* __cdecl memmove(void*, const void*, unsigned int);                            // 0x011E0744
int __cdecl GetTime64();
const char* __cdecl HeaderFieldToFieldString(int field);
__int64 __cdecl ParseInt64(const char* s, int, int);
typedef void (__thiscall *VFV2)(void*, void*, unsigned);
typedef int  (__thiscall *VFI)(void*);
typedef int  (__thiscall *VFI1)(void*, int);
typedef char (__thiscall *VFC1)(void*, int);
typedef char (__thiscall *VFC2)(void*, void*, int);
typedef int  (__thiscall *VFI3)(void*, void*, unsigned, int);
#define VSLOT(p, off) ((*(void***)(p))[(off) / 4])
#define VC0(p, off)   ((VFI)VSLOT(p, off))(p)
#define VC3(p, off, a, b, c) ((VFI3)VSLOT(p, off))(p, (void*)(a), (unsigned)(b), (int)(c))
namespace eastl {
struct StrStub {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    int   mAllocPad;
    void assign(const char* first, const char* last);        // 0x00454CB0
    void assignRange(const char* first, const char* last);   // 0x00942E50 (this slice)
};
}
namespace eastl {
struct FixedStub {
    char data[0x100];
    void assign(const char* first, const char* last);        // 0x0060A2C0
};
}
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
namespace EA {
namespace Internet {
struct WorkerThreadInfo_s0094_2290 {
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
}
}
namespace EA {
namespace Internet {
struct Job_s0094_2290 {
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
}
}
namespace EA {
namespace Internet {
class HTTPClient_s0094_2290 {
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
    WorkerThreadInfo_s0094_2290* mpWorkerThreadInfo; // +0x90
    char  pad94[0x130 - 0x94];
    unsigned __int64 mnBytesSent;         // +0x130
    unsigned __int64 mnBytesReceived;     // +0x138
    char* mpReadBuffer;                   // +0x140
    unsigned int mnReadBufferSize;        // +0x144
    char* mpWriteBuffer;                  // +0x148
    unsigned int mnWriteBufferSize;       // +0x14c

    bool  ReadRawBody(WorkerThreadInfo_s0094_2290* wti, char* pBuf);                          // 00942290 0x00942290
    int   ReadResponseLine(WorkerThreadInfo_s0094_2290* wti, char* pBuf, int nMax, char tr);  // 009423D0 0x009423d0
    bool  DoJobUpdate(int job, unsigned doneLo, unsigned doneHi,
                      unsigned totalLo, int totalHi, unsigned* progress);          // 00942530
    __int64 ReadResponseData(WorkerThreadInfo_s0094_2290* wti, unsigned totalLo,
                             unsigned totalHi, char notify);                        // 00942690
    __int64 ReadChunkedResponseData(WorkerThreadInfo_s0094_2290* wti);                         // 009428B0 0x009428b0
    bool  ReadResponseBody(WorkerThreadInfo_s0094_2290* wti);                                 // 00942B40 0x00942b40
    void  __declspec(noinline) SetUserAgent(const char* p);                        // 00942FB0
};
}
}
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
Cookie40::~Cookie40() {}
static int StrLen(const char* s) {
    const char* p = s;
    while (*p) ++p;
    return (int)(p - s);
}
struct HTTPClientRd64 {
    __int64 ReadResponseData64(EA::Internet::WorkerThreadInfo_s0094_2290* wti, unsigned totalLo, unsigned totalHi, char notify); // 0x00942690
};
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

// ---- items of slice s00942290 end

// ---- items of slice s00942ff0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" const char* HTTPMethodToString(int method);   // 0x00941BC0
extern unsigned kTimeoutForever;                  // 0x0143f214 (-1)
extern "C" unsigned long __stdcall GetThreadTime(void);   // 0x0094d340 (jmp thunk)
extern char gEmptyBuf[];                                    // 0x01667bac
extern char kIID_SockQI[];                                  // 0x0164c507
void* __cdecl operator_new(unsigned int size, const char* name, int a, int b,
                           const char* file, int line);   // 0x00f473a0
namespace eastl {
struct StrStub_s0094_2ff0 {
    char* mpBegin;      // +0x00
    char* mpEnd;        // +0x04
    char* mpCapacity;   // +0x08
    int   mnAllocPad;   // +0x0c
    char* mpSelf;       // +0x10  (points at mBuffer)
    char  mBuffer[0x40];// +0x14
    StrStub_s0094_2ff0() {}                                        // (not emitted: no default use)
    StrStub_s0094_2ff0(const StrStub_s0094_2ff0& o) {                         // SSO copy ctor
        mpSelf = mBuffer;
        mpCapacity = mBuffer + 0x40;
        mpEnd = mBuffer;
        mpBegin = mBuffer;
        *mBuffer = 0;
        assignRange(o.mpBegin, o.mpEnd);  // 0x00942e50 (eastl::StrStub::assignRange)
    }
    StrStub_s0094_2ff0& operator=(const StrStub_s0094_2ff0& o) {
        if (this != &o) {
            if (mpBegin != mpEnd) {
                *mpBegin = 0;
                mpEnd = mpBegin;
            }
            assignRange(o.mpBegin, o.mpEnd);  // 0x00942e50 (eastl::StrStub::assignRange)
        }
        return *this;
    }
    void assignRange(const char* first, const char* last);   // 0x00942E50 (slice 49)
    StrStub_s0094_2ff0* assign(const char* s);                          // 0x00943570
};
}
typedef eastl::StrStub_s0094_2ff0 JobString;
struct Job {
    JobString first;    // +0x00
    JobString second;   // +0x54
    Job(const Job& s);                  // 0x00943650
    Job& operator=(const Job& s);       // 0x009436B0
};
struct RefObj_s0094_2ff0 {
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
inline void ReleaseRefObj(RefObj_s0094_2ff0* p) {
    if (p) {
        int rc = _InterlockedDecrement((volatile long*)&p->mnRefCount);
        if (rc == 0) {
            _InterlockedExchange((volatile long*)&p->mnRefCount, 1);
            if (p)
                p->Destroy(1);
        }
    }
}
struct Cookie40_s0094_2ff0 {
    int      m00[7];      // +0x00
    RefObj_s0094_2ff0*  mp1c;        // +0x1c
    int      m20;         // +0x20
    RefObj_s0094_2ff0*  mp24;        // +0x24
    int      m28;         // +0x28
    int      m2c;         // +0x2c
    unsigned __int64 m30; // +0x30
    unsigned __int64 m38; // +0x38
    Cookie40_s0094_2ff0(const Cookie40_s0094_2ff0&);   // 0x00942CE0 (slice 49)
};
struct CookieNode {
    CookieNode* mpNext;   // +0x00
    CookieNode* mpPrev;   // +0x04
    Cookie40_s0094_2ff0    mData;    // +0x08
    void insertBeforeSelf(const Cookie40_s0094_2ff0& src);   // 0x00943600
};
struct CookieList {
    CookieNode* mpNode;   // +0x00
    void insertAtNext(const Cookie40_s0094_2ff0& src);       // 0x009435B0
};
static const char kEastlFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
static const char kEastlName[] = "EASTL";
static inline void InsertBefore(CookieNode* at, const Cookie40_s0094_2ff0& src) {
    CookieNode* node = (CookieNode*)operator_new(0x48, kEastlName, 0, 0, kEastlFile, 0xd1);
    new (&node->mData) Cookie40_s0094_2ff0(src);
    node->mpNext = at;
    node->mpPrev = at->mpPrev;
    at->mpPrev->mpNext = node;
    at->mpPrev = node;
}
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
void __stdcall JobDestroyRange(Job* first, Job* last);  // 0x00943420 (defined below; used by a stub's inline body)
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
struct WorkerThreadInfo;
__declspec(dllimport) long __cdecl atol(const char*);
struct HTTPClient_s0094_2ff0 {
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
struct EAMutex {
    unsigned int pad[12];
    int Lock(const unsigned* timeout);            // 0x009221b0 (ret 4)
    int Unlock();                                 // 0x00922270
};
struct ThreadRef {
    void* mpData;
    ThreadRef* Init();                            // 0x00743b50 (this->mpData = 0, returns this)
    void CopyFrom(const ThreadRef* o);            // 0x00922c20 (ret 4; copy + lock xadd +1)
    void Release();                               // 0x00922e10 (lock xadd -1, free at zero)
    int WaitForEnd(const unsigned* timeout, int* status);   // 0x00922940 (ret 8)
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
static __forceinline void EraseBefore(CookieNode* pos) {
    CookieNode* n = pos->mpPrev;
    n->mpPrev->mpNext = n->mpNext;
    n->mpNext->mpPrev = n->mpPrev;
    if (n->mData.mp24) n->mData.mp24->Release();
    if (n->mData.mp1c) n->mData.mp1c->Release();
    operator_delete__(n);
}
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
// ---- items of slice s00942ff0 end

// ---- items of slice s00945ed0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace EA {
namespace Internet {
struct Thread {
    Thread();
    void Begin(void* fn, void* arg, int, int prio);   // FUN_00922f30
    void WaitForEnd();                                // FUN_00922e10
};
}
}
void* __cdecl operator new(unsigned int, const char*, int, int, int, int);
namespace eastl {
struct StrStub_s0094_5ed0 {
    char* mpBegin;
    char* mpEnd;
    char* mpCapacity;
    int   mAlloc;
    void assign(const char* first, const char* last);  // 0x00943570 (eastl::StrStub::assign)
    void append(const char* first, const char* last);   // 0x00455d60
    void appendFixed(const char* first, const char* last);   // 0x0060a150 (fixed_string<char>::append)
    ~StrStub_s0094_5ed0() {
        if (mpCapacity - mpBegin > 1 && mpBegin)
            operator_delete__(mpBegin);
    }
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    const char* data() const { return mpBegin; }
};
}
namespace EA {
namespace Internet {
struct IStr {
virtual void v0();
virtual void v1();
virtual void v2();
virtual void v3();
virtual void v4();
    virtual int  GetState();                        // 5  (+0x14)
    virtual void v6();
    virtual unsigned GetSize();                     // 7  (+0x1c)
    virtual void v8();
    virtual int  GetPos(int);                       // 9  (+0x24)
    virtual bool SetPos(int, int);                  // 10 (+0x28)
virtual void v11();
virtual void v12();
virtual void v13();
    virtual int  Write(const void*, unsigned);      // 14 (+0x38)
};
}
}
namespace EA {
namespace Internet {
struct Mutex {
    void Lock(const void* timeout);
    void Unlock();
};
}
}
namespace EA {
namespace Internet {
struct Thread_s0094_5ed0 {
    Thread_s0094_5ed0();
    void Begin(void* fn, void* arg, int, int prio);   // FUN_00922f30
    void WaitForEnd();                                // FUN_00922e10
};
}
}
namespace EA {
namespace Internet {
int GetThreadPriorityDefault();                       // FUN_00922920
}
}
namespace EA {
namespace Internet {
void __cdecl ThreadSleep(const void* t);              // EA::Thread::ThreadSleep
}
}
namespace EA {
namespace Internet {
int __cdecl GetTime64();                              // FUN_00941bb0
}
}
namespace EA {
namespace Internet {
char* __cdecl Sprintf8(char* buf, const char* fmt, ...);   // 0x00938470
}
}
namespace EA {
namespace Internet {
const char* __cdecl HeaderFieldToFieldString(int field);
}
}
namespace EA {
namespace Internet {
extern char g_logBuf[];                               // 0x0166A9D8
}
}
namespace EA {
namespace Internet {
extern const int kLockTimeout;                        // 0x0143F214
}
}
namespace EA {
namespace Internet {
extern const int kSleepTime;                          // 0x0143F218
}
}
namespace EA {
namespace Internet {
class HTTPClient_s0094_5ed0;
}
}
namespace EA {
namespace Internet {
template <class T>
struct AutoRefCount_s0094_5ed0 {
    T* mp;
    AutoRefCount_s0094_5ed0() : mp(0) {}
    void Set(T* p);                  // out of line (AddRef new, Release old): FUN_008fd240
};
}
}
namespace EA {
namespace Internet {
struct IUnkStub {
    virtual int AddRef();
    virtual int Release();
};
}
}
namespace EA {
namespace Internet {
struct ISockOpt {
virtual void s0();
virtual void s1();
virtual void s2();
virtual void s3();
virtual void s4();
virtual void s5();
virtual void s6();
virtual void s7();
virtual void s8();
virtual void s9();
virtual void s10();
virtual void s11();
    virtual void Shutdown(int how);         // slot 12 (+0x30)
};
}
}
namespace EA {
namespace Internet {
struct ISock : IUnkStub {
    virtual void s2();
    virtual void s3();
    virtual ISockOpt* GetOptions();         // slot 4 (+0x10)
};
}
}
namespace EA {
namespace Internet {
struct RefObj_s0094_5ed0 {
    virtual void Destroy(int flags);
    int mnRefCount;
};
}
}
namespace EA {
namespace Internet {
inline void ReleaseRefObj_s0094_5ed0(RefObj_s0094_5ed0* p) {
    if (p) {
        int n = _InterlockedExchangeAdd((volatile long*)&p->mnRefCount, -1);
        if (n - 1 == 0) {
            _InterlockedExchange((volatile long*)&p->mnRefCount, 1);
            if (p)
                p->Destroy(1);
        }
    }
}
}
}
namespace EA {
namespace Internet {
struct IFilter {
    virtual void f0();
    virtual void f1();
    virtual bool OnResponse(void* resp);    // slot 2 (+8)
    virtual bool OnRequest(void* req);      // slot 3 (+0xc)
};
}
}
namespace EA {
namespace Internet {
struct IRef3 {
    virtual void f0();
    virtual void AddRef();                  // +4
    virtual void Release();                 // +8
};
}
}
namespace EA {
namespace Internet {
struct IBodyStream {
virtual void f0();
virtual void f1();
virtual void f2();
virtual void f3();
virtual void f4();
virtual void f5();
    virtual void Close();                   // slot 6 (+0x18)
};
}
}
namespace EA {
namespace Internet {
struct IChecker {
    virtual void f0();
    virtual bool Check(void* resp);         // slot 1 (+4)
};
}
}
namespace EA {
namespace Internet {
struct HeaderList {
    bool FindHeader(const char* name, const char** out, int);   // FUN_00942050
};
}
}
namespace EA {
namespace Internet {
struct HTTPResponse_s0094_5ed0 {
    int  pad0[2];
    eastl::StrStub_s0094_5ed0 msBody;           // +8   (basic_string head only)
    char pad1[0x21c - 0x18];
    eastl::StrStub_s0094_5ed0 msStr21c;         // +0x21c
    char pad2[0x430 - 0x22c];
    int  nStatus;                    // +0x430
    unsigned nMajor;                 // +0x434
    unsigned nMinor;                 // +0x438
    int  nHasHeaders;                // +0x43c
    char pad3[0x4a4 - 0x440];
    HeaderList headers;              // +0x4a4
    char pad4[0xf3c - 0x4a5];
    IRef3* mpExtra;                  // +0xf3c
    HTTPResponse_s0094_5ed0();                  // FUN_00943de0, 0xf40-byte object
};
}
}
namespace EA {
namespace Internet {
struct UrlHolder_s0094_5ed0 {
    eastl::StrStub_s0094_5ed0* GetString();     // FUN_0097e850 (symbol name there is misattributed)
};
}
}
namespace EA {
namespace Internet {
struct HTTPRequestStub {
    char pad0[8];
    char* mpUrlBegin;                // +8
    char* mpUrlEnd;                  // +0xc
    char pad1[0x30 - 0x10];
    UrlHolder_s0094_5ed0 urlHolder;             // +0x30
    char pad2[0xe0 - 0x31];
    eastl::StrStub_s0094_5ed0 msStrE0;          // +0xe0
    char pad3[0xd8c - 0xf0];
    IBodyStream* mpBody;             // +0xd8c
    IRef3* mpExtra;                  // +0xd90
    IChecker* mpChecker;             // +0xd94
};
}
}
namespace EA {
namespace Internet {
struct Job_s0094_5ed0 {
    unsigned id;                     // +0
    int      state;                  // +4
    int      userData;               // +8  (timeout seconds)
    int      z0;                     // +0xc (deadline)
    int      one;                    // +0x10
    int      z1;                     // +0x14 (progress)
    int      z2;                     // +0x18
    AutoRefCount_s0094_5ed0<HTTPRequestStub> mpRequest;   // +0x1c
    bool     bFlag;                  // +0x20
    AutoRefCount_s0094_5ed0<HTTPResponse_s0094_5ed0> mpResponse;     // +0x24
    int      arg;                    // +0x28
    int      pad2c;                  // +0x2c
    int      z3[4];                  // +0x30
    Job_s0094_5ed0() {}
    ~Job_s0094_5ed0();                              // FUN_00942630
    void Assign(const Job_s0094_5ed0* o);           // FUN_00942d70
};
}
}
namespace EA {
namespace Internet {
struct JobNode {
    JobNode* next;
    JobNode* prev;
    Job_s0094_5ed0 job;                         // +8
};
}
}
namespace EA {
namespace Internet {
struct EmptyStr : eastl::StrStub_s0094_5ed0 {
    EmptyStr() {
        mpBegin = (char*)0x1667bac;
        mpEnd = (char*)0x1667bac;
        mpCapacity = (char*)0x1667bad;
    }
};
}
}
namespace EA {
namespace Internet {
struct WorkerThreadInfo_s0094_5ed0 {
    HTTPClient_s0094_5ed0* mpOwner;             // +0
    bool bCreated;                   // +4
    bool bShouldQuit;                // +5
    bool bCancel;                    // +6
    int  pauseCount;                 // +8
    EmptyStr msServer;               // +0xc
    unsigned short nPort;            // +0x1c
    ISock* mpSocket;                 // +0x20
    int  protocol;                   // +0x24
    bool bV11;                       // +0x28
    Job_s0094_5ed0* mpCurrentJob;               // +0x2c
    Thread_s0094_5ed0 mThread;                  // +0x30
    WorkerThreadInfo_s0094_5ed0() : mpOwner(0), mpSocket(0) {}
};
}
}
namespace EA {
namespace Internet {
struct JobListAnchor {
    JobNode* next;
    JobNode* prev;
    void Push(const Job_s0094_5ed0* j);         // FUN_00943600 (list push_back)
};
}
}
namespace EA {
namespace Internet {
typedef void (__cdecl *NotifyFn)(void* ctx, void* client, unsigned msg, void* data, int zero);
}
}
namespace EA {
namespace Internet {
class HTTPClient_s0094_5ed0 : public IUnkStub {
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
    WorkerThreadInfo_s0094_5ed0* mpWorkerThreadInfo;   // +0x90
    JobListAnchor mJobList;          // +0x94
    char pad6[0x128 - 0x9c];
    int  mnDefaultTimeout;           // +0x128
    char pad7[0x150 - 0x12c];
    IFilter** mpFiltersBegin;        // +0x150
    IFilter** mpFiltersEnd;          // +0x154

    void CreateWorkerThreadIfNeeded();  // 0x00946540 (EA::Internet::HTTPClient::CreateWorkerThreadIfNeeded)
    unsigned AddNewJob(HTTPRequestStub* req, int arg3, bool arg4, int arg5);  // 0x00946680 (EA::Internet::HTTPClient::AddNewJob)
    unsigned WorkerThreadFunction(WorkerThreadInfo_s0094_5ed0* info);  // 0x00945ed0 (EA::Internet::HTTPClient::WorkerThreadFunction)
    static unsigned StaticWorkerThreadFunction(WorkerThreadInfo_s0094_5ed0* info);

    bool Fn942ff0(WorkerThreadInfo_s0094_5ed0* info);
    bool Fn944f40(WorkerThreadInfo_s0094_5ed0* info);
    bool Fn944e10(WorkerThreadInfo_s0094_5ed0* info, int);
    bool WriteRequestBody(WorkerThreadInfo_s0094_5ed0* info);  // 0x00945c80 (EA::Internet::HTTPClient::WriteRequestBody)
    bool Fn9453f0(WorkerThreadInfo_s0094_5ed0* info);
    bool ReadResponseBody(WorkerThreadInfo_s0094_5ed0* info);  // 0x00942b40 (EA::Internet::HTTPClient::ReadResponseBody)
    int  Fn945a10(WorkerThreadInfo_s0094_5ed0* info);
    void Pump(ISock* socket);
};
}
}
namespace EA {
namespace Internet {
static inline const char* CharStrEnd(const char* p) {
    const char* e = p;
    while (*e++)
        ;
    return e - 1;
}
}
}
// ---- items of slice s00945ed0 end

// ---- items of slice s00943f60 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void (__thiscall *VF0)(void*);
typedef int  (__thiscall *VFI0)(void*);
#define VSLOT_s0094_3f60(p, byteoff) ((*(void***)(p))[(byteoff) / 4])
#define VCALL0(p, off)    ((VF0)VSLOT_s0094_3f60(p, off))(p)
#define VCALLI0(p, off)   ((VFI0)VSLOT_s0094_3f60(p, off))(p)
namespace EA {
namespace Thread {
struct Mutex_s0094_3f60 {
    void Lock(const void* timeout);   // 0x009221b0
    void Unlock();                    // 0x00922270
};
}
}
namespace EA {
namespace Internet {
struct RefObj_s0094_3f60 {
    virtual void Destroy(int flags);
    int mnRefCount;
};
}
}
namespace EA {
namespace Internet {
struct WorkerThreadInfo_s0094_3f60 {
    int   pad0;
    char  bCreated;                   // +4
    char  pad1[0x20 - 5];
    void* mpSocket;                   // +0x20
};
}
}
namespace EA {
namespace Internet {
class HTTPClient_s0094_3f60 {
public:
    char pad0[0xc];
    bool mbInitialized;               // +0xc
    char pad1[0x24 - 0xd];
    NotifyFn mpNotify;                // +0x24
    void* mpNotifyCtx;                // +0x28
    char pad2[0x54 - 0x2c];
    void* mpLogB;                     // +0x54
    void* mpLogA;                     // +0x58
    char pad3[0x60 - 0x5c];
    EA::Thread::Mutex_s0094_3f60 mMutex;         // +0x60
    char pad4[0x90 - 0x61];
    WorkerThreadInfo_s0094_3f60* mpWorkerThreadInfo;   // +0x90
    char pad5[0x140 - 0x94];
    char* mpReadBuffer;               // +0x140
    char pad7[0x148 - 0x144];
    char* mpWriteBuffer;              // +0x148 (freed when non-null)
    char pad6[0x150 - 0x14c];
    RefObj_s0094_3f60** mpFiltersBegin;          // +0x150
    RefObj_s0094_3f60** mpFiltersEnd;            // +0x154

    void SetTimeout(int a, int ms);   // 0x00943a30
    void Pump(void* socket);          // 0x009421b0
    bool Shutdown();
};
}
}
// ---- items of slice s00943f60 end

// ---- items of slice s00944f40 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" char* __cdecl _ultoa(unsigned long value, char* buf, int radix);   // msvcr90
extern "C" void  __cdecl HTTPClientSendCallback(int sent, const char* buf, int n);  // 0x00942110
extern "C" bool  __cdecl Fn94ba30(const char* s);                     // 0x0094ba30
extern "C" const char* __cdecl GetPoliticalID(void* gameData);        // 0x0097e850
extern "C" void  __cdecl StrDtor(void* s);                            // 0x00530670
extern "C" void  __cdecl AtomicRefRelease(void* p);                   // 0x0060d210
extern "C" int   __cdecl Sprintf8_s0094_4f40(char* buf, const char* fmt, ...);   // 0x00938470
static __forceinline const char* CharStrEnd_s0094_4f40(const char* p) {
    const char* e = p;
    while (*e) ++e;
    return e;
}
typedef void* (__thiscall *VF_This0)(void*);
typedef int   (__thiscall *VF_I0)(void*);
typedef int   (__thiscall *VF_I2)(void*, void*, int);
typedef int   (__thiscall *VF_I3)(void*, void*, int, int);
typedef bool  (__thiscall *VF_B0)(void*);
typedef bool  (__thiscall *VF_B1)(void*, int);
typedef bool  (__thiscall *VF_BS)(void*, void*);
typedef bool  (__thiscall *VF_B2)(void*, int, int);
#define VS(p, off) (*(void***)(p))[(off) / 4]
struct Str {
    char* mpBegin;      // +0x00
    char* mpEnd;        // +0x04
    char* mpCapacity;   // +0x08
    void assign(const char* s);                          // 0x00943570
    void assignRange(const char* first, const char* last);  // 0x00942e50
    void append(const char* first, const char* last);    // 0x0060a150
};
static void StrClear(Str& s) {
    if (s.mpBegin != s.mpEnd) {
        *s.mpBegin = 0;
        s.mpEnd = s.mpBegin;
    }
}
struct FStr {
    char* mpBegin;      // +0x00
    char* mpEnd;        // +0x04
    char* mpCapacity;   // +0x08
    char* mpField0c;    // +0x0c
    char* mpField10;    // +0x10
    char  mBuffer[0x200];   // +0x14 (inline fixed_string storage)
    void append(const char* first, const char* last);    // 0x0060a150 (fixed_string::append)
    void append(char c);                                 // 0x00944250
    void Init() {
        mpBegin = mBuffer;
        mpEnd = mBuffer;
        mpCapacity = mBuffer + 0x200;
        mpField10 = mBuffer;
        mBuffer[0] = 0;
    }
    void Append(const char* s) { append(s, CharStrEnd_s0094_4f40(s)); }
};
struct URL {
    Str* GetPart(int which);   // 0x0094baf0
    int  GetPort();            // 0x0094a4a0
    void SetURL(const char* url, bool flag);   // 0x0094a6a0
    void Fn94bb50(const char* location, char* out);   // 0x0094bb50
};
struct HeaderNode {
    Str   msName;       // +0x00
    char  pad0c[0x54 - 0x0c];
    Str   msValue;      // +0x54
    char  pad60[0xa8 - 0x60];
};
struct HeaderList_s0094_4f40 {
    HeaderNode* mpBegin;   // +0x00
    HeaderNode* mpEnd;     // +0x04
    bool FindHeader(const char* name, void* out, int index);   // 0x00942050
    void AddHeaderPtr(int field, const void* v);               // 0x00944d50
    void AddHeaderStr(int field, const char* v);               // 0x00944db0
    void SetHeaderId(const char* field, int id);               // 0x00944a30
    void AddNode();                                            // 0x00944af0
};
struct Req {
    char  pad00[0x04];
    int   mnRefCount;  // +0x04
    Str   msMethod;    // +0x08
    char  pad14[0x2c - 0x14];
    int   mnField2c;   // +0x2c
    char  urlSpace[0x2f4 - 0x30];
    char  pad2fc[0xd8c - 0x2f4];
    void* mpStreamD8c; // +0xd8c
    void* mpStreamD90; // +0xd90
    URL* url() { return (URL*)((char*)this + 0x30); }
    HeaderList_s0094_4f40* headers() { return (HeaderList_s0094_4f40*)((char*)this + 0x2f4); }
    void* ctor();                   // 0x009442e0
    void SetMethod(int m);          // 0x009438c0
    void SetURL(const char* u);     // 0x00942f70
    void Fn615c10(void* p);         // 0x00615c10
    void Fn615bd0(void* p);         // 0x00615bd0
};
struct Resp {
    char pad00[0x43c];
    int  mnStatus;     // +0x43c
    HeaderList_s0094_4f40* headers4a4() { return (HeaderList_s0094_4f40*)((char*)this + 0x4a4); }
    bool Clear();      // 0x00944bd0
};
struct Job_s0094_4f40 {
    char  pad00[0x04];
    int   mResult;             // +0x04
    char  pad08[0x10 - 0x08];
    int   mnField10;           // +0x10
    int   mnField14;           // +0x14
    int   mnRedirectionCount;  // +0x18
    Req*  mpRequest;           // +0x1c
    char  pad20[0x24 - 0x20];
    Resp* mpResponse;          // +0x24
    char  pad28[0x38 - 0x28];
    unsigned long long mnUploadBodySize;   // +0x38
};
struct Info {                        // HTTPClient::WorkerThreadInfo
    char   pad00[0x04];
    char   mbShouldQuit;             // +0x05
    char   mbCancelCurrent;          // +0x06
    char   pad07[0x20 - 0x07];
    void*  mpSocket;                 // +0x20
    char   pad24[0x2c - 0x24];
    Job_s0094_4f40*   mpCurrentJob;             // +0x2c
};
struct Mutex_s0094_4f40 {  // 0x009221b0 / 0x00922270
    void Lock(unsigned timeout);
    void Unlock();
};
struct CookieList_s0094_4f40 { void insertAtNext(const void* src); };       // 0x009435b0
struct HTTPClient_s0094_4f40 {
    char      pad00[0x0c];
    bool      mbInitialized;         // +0x0c
    char      pad0d[0x14 - 0x0d];
    Str       msUserAgent;           // +0x14
    char      pad20[0x60 - 0x20];
    Mutex_s0094_4f40     mMutex;                // +0x60
    char      pad70[0x114 - 0x70];
    Str       msProxyServerAddress;  // +0x114
    char      pad120[0x128 - 0x120];
    int       mnTimeoutSeconds;      // +0x128
    char      pad12c[0x130 - 0x12c];
    unsigned long long mnBytesSent;  // +0x130
    char      pad138[0x140 - 0x138];
    char*     mpReadBuffer;          // +0x140
    unsigned  mnReadBufferSize;      // +0x144
    char*     mpWriteBuffer;         // +0x148
    unsigned  mnWriteBufferSize;     // +0x14c

    CookieList_s0094_4f40* cookieList() { return (CookieList_s0094_4f40*)((char*)this + 0x94); }

    int  ReadRawBody(Info* info, char* buf);          // 0x00942290
    int  ReadResponseLine(Info* info, char* buf, int len, char flag);   // 0x009423d0
    int  ParseResponseStatus(Info* info);             // 0x00943bd0
    bool Fn944f40(Info* info);                        // 0x00944f40
    bool Fn9453f0(Info* info);                        // 0x009453f0
    bool Fn9458c0(Job_s0094_4f40* job);                          // 0x009458c0
    int  Fn945a10(Info* info);                        // 0x00945a10
    bool WriteRequestBody(Info* info);                // 0x00945c80
};
struct HTTPRequest_s0094_4f40 {
    static bool CreateHTTPPostRequest(const char* url, void* body, void* image, Req** out);  // 0x00945b20 (HTTPRequest::CreateHTTPPostRequest)
};
// ---- items of slice s00944f40 end

// @ 0x00941f20
bool HTTPClient::AllocBuffer()
{
    int self = (int)this;
    if (*(char*)(self + 0xc) == 0) {
        void* p = operator_new_6(*(uint32_t*)(self + 0x144),
                                 "UTFInternet/char8_t", 0, 0, 0, 0);
        *(void**)(self + 0x140) = p;
        *(char*)(self + 0xc) = 1;
    }
    return true;
}

// @ 0x00941f90
bool __stdcall HTTPClientAllocateSocket(int obj, void** out)
{
    *out = 0;
    if (((SockMgr*)obj)->FUN_0094BAA0() == 3) {
        void* mgr = FUN_0094F0D0();
        if (mgr != 0) {
            void* sock = ((SockMgr*)mgr)->FUN_0094F030();
            if (sock != 0) {
                void* r = (*(void*(__thiscall**)(void*))((char*)*(void**)sock + 4))(sock);
                *out = r;
                return *out != 0;
            }
        }
    } else {
        void* conn = FUN_0094CD40();
        if (conn != 0) {
            void* r = (*(void*(__thiscall**)(void*, int))((char*)*(void**)conn + 0x18))(conn, 3);
            if (r != 0 && (void*)((char*)r + 8) != 0) {
                void* s = (*(void*(__thiscall**)(void*, unsigned))((char*)*(void**)((char*)r + 8) + 0xc))(
                    (char*)r + 8, 0x23e12222);
                if (s != 0)
                    *out = s;
            }
        }
    }
    return *out != 0;
}

// @ 0x00942010
bool __stdcall HTTPClientCheckTimeout(int self, int* timeout)
{
    if (*(int*)(self + 0xc) > 0) {
        __int64 now = GetTime64();
        if (*(int*)(self + 0xc) < (int)now)
            return true;
        if (*timeout > 0) {
            *(int*)(self + 0xc) = *(int*)(self + 8) + (int)now;
            *timeout = 0;
        }
    }
    return false;
}

// @ 0x00942050
bool HTTPClient::FindHeader(char* name, void* out, int index)
{
    int* self = (int*)this;
    int count = (self[1] - *self) / 0xa8;
    int found = 0;
    for (int i = 0; i < count; i++) {
        if (_stricmp(name, *(char**)(*self + i * 0xa8)) == 0) {
            if (found == index) {
                if (out != 0)
                    *(int*)out = *(int*)(i * 0xa8 + *self + 0x54);
                return true;
            }
            found++;
        }
    }
    return false;
}

// @ 0x009420e0
bool HTTPClient::FindHeaderByField(int field, void* out, int index)
{
    const char* name = HeaderFieldToFieldString(field);
    return FindHeader((char*)name, out, index);
}

// @ 0x00942110
int HTTPClient::SendCallback(const char* data, int len)
{
    int self = (int)this;
    if (len == -1) {
        const char* p = data;
        do {
        } while (*p++ != 0);
        len = (int)(p - (data + 1));
    }
    if (*(int*)(self + 0x30) > 0) {
        void* obj = *(void**)(self + 0x58);
        void** vtbl = *(void***)obj;
        volatile int cb = ((int(__thiscall*)(void*, const char*, int))vtbl[0x38 / 4])(obj, data, len);
        return cb;
    }
    return len;
}

// @ 0x00942150
void EA::Internet::HTTPClient::SetNotificationTarget(void (__cdecl *target)(void *, EA::Internet::HTTPClient *, unsigned int, EA::Internet::HTTPClient::Job *, EA::Internet::HTTPClient::JobUpdate *), void * ctx)
{
    int self = (int)this;
    void* old = *(void**)(self + 0x24);
    if (old == target) {
        *(void**)(self + 0x28) = ctx;
        return;
    }
    if (old != 0) {
        typedef void (__cdecl* Fn)(void*, int, unsigned, int, int);
        ((Fn)old)(*(void**)(self + 0x28), self, 0x700af201, 0, 0);
    }
    *(void**)(self + 0x24) = target;
    *(void**)(self + 0x28) = ctx;
    if (target != 0) {
        typedef void (__cdecl* Fn)(void*, int, unsigned, int, int);
        ((Fn)target)(ctx, self, 0x700af200, 0, 0);
    }
}

// @ 0x009421b0
#pragma intrinsic(strlen)
void HTTPClient::Pump(int* stream)
{
    if (stream == 0)
        return;
    int* sub = (int*)(*(int*(__thiscall**)(int*))(*stream + 0x10))(stream);
    if ((*(char(__thiscall**)(int*))(*sub + 0x20))(sub) == 0)
        return;
    (*(void(__thiscall**)(int*, int))(*stream + 0x18))(stream, 1);
    if ((*(int(__thiscall**)(int*))(*stream + 0x2c))(stream) == 2) {
        do {
            sub = (int*)(*(int*(__thiscall**)(int*))(*stream + 0x10))(stream);
            if ((*(char(__thiscall**)(int*, int))(*sub + 0x64))(sub, 0) == 0)
                break;
            int n = (*(int(__thiscall**)(int*, int, int, int))(*stream + 0x44))(
                stream, *(int*)((char*)this + 0x140), *(int*)((char*)this + 0x144), 0);
            if (n <= 0)
                break;
            const char* buf = *(const char**)((char*)this + 0x140);
            int m = n;
            if (n == -1)
                m = (int)strlen(buf);
            if (*(int*)((char*)this + 0x30) > 0) {
                void* log = *(void**)((char*)this + 0x54);
                (*(void(__thiscall**)(void*, const char*, int))((char*)*(void**)log + 0x38))(log, buf, m);
            }
            *(unsigned __int64*)((char*)this + 0x138) += (unsigned)n;
        } while ((*(int(__thiscall**)(int*))(*stream + 0x2c))(stream) == 2);
    }
    (*(void(__thiscall**)(int*))(*stream + 0x14))(stream);
}

// @ 0x00942290
bool EA::Internet::HTTPClient_s0094_2290::ReadRawBody(EA::Internet::WorkerThreadInfo_s0094_2290* wti, char* pBuf)
{
    int remaining = StrLen(pBuf);
    unsigned consumed = 0;
    while (remaining != 0 && wti->mbCancelCurrent == 0 && wti->mbShouldQuit == 0) {
        EA::Internet::Job_s0094_2290* job = (EA::Internet::Job_s0094_2290*)wti->mpCurrentJob;
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

// @ 0x009423d0
int EA::Internet::HTTPClient_s0094_2290::ReadResponseLine(EA::Internet::WorkerThreadInfo_s0094_2290* wti, char* pBuf, int nMax, char trim)
{
    if (pBuf == 0 || nMax < 1) { ((EA::Internet::Job_s0094_2290*)wti->mpCurrentJob)->mResult = 3; return -1; }
    int nReadOK = 0;
    int i = 0;
    char* p = pBuf;
    for (;;) {
        EA::Internet::Job_s0094_2290* job = (EA::Internet::Job_s0094_2290*)wti->mpCurrentJob;
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

// @ 0x00942530
bool EA::Internet::HTTPClient_s0094_2290::DoJobUpdate(int job, unsigned doneLo, unsigned doneHi, unsigned totalLo, int totalHi, unsigned* progress)
{
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

// @ 0x00942630
// Cookie40 destructor (implicit): the forcing function below makes the compiler emit it out of line
#pragma auto_inline(off)
void rwForceEmit_Cookie40_dtor(Cookie40* p)
{
    p->~Cookie40();
}
#pragma auto_inline(on)

// @ 0x00942690
__int64 EA::Internet::HTTPClient_s0094_2290::ReadResponseData(EA::Internet::WorkerThreadInfo_s0094_2290* wti, unsigned totalLo, unsigned totalHi, char notify)
{
    __int64 remain = ((__int64)(int)totalHi << 32) | (unsigned)totalLo;
    __int64 done = 0;
    unsigned prog = 0;
    int prevN = 0;
    for (;;) {
        if (remain == 0 ||
            wti->mbCancelCurrent != 0 || wti->mbShouldQuit != 0)
            break;
        EA::Internet::Job_s0094_2290* job = (EA::Internet::Job_s0094_2290*)wti->mpCurrentJob;
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
                EA::Internet::Job_s0094_2290* jb = (EA::Internet::Job_s0094_2290*)wti->mpCurrentJob;
                jb->mnLastNotifySize = (unsigned __int64)done;
            }
            break;
        }
        mnBytesReceived += n;
        // When the socket returned -1 the log line is the partial buffer contents, so its
        // length is strlen(mpReadBuffer); otherwise it is the raw byte count.
        unsigned logLen = n;
        if ((int)n == -1) logLen = (unsigned)strlen(mpReadBuffer);
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
    EA::Internet::Job_s0094_2290* jb = (EA::Internet::Job_s0094_2290*)wti->mpCurrentJob;
    jb->mnLastNotifySize = (unsigned __int64)done;
    return done;
}

// @ 0x009428b0
__int64 EA::Internet::HTTPClient_s0094_2290::ReadChunkedResponseData(EA::Internet::WorkerThreadInfo_s0094_2290* wti)
{
    __int64 total = 0;
    for (;;) {
        __int64 n = ReadResponseLine(wti, mpReadBuffer, mnReadBufferSize, 0);
        if (n < 0) { total = n; break; }
        // scan the hex digits of the chunk-size line
        __int64 i;
        for (i = 0; i < n && isxdigit(mpReadBuffer[i]); ++i) {}
        if (i <= 0 || i == n) {
            ((EA::Internet::Job_s0094_2290*)wti->mpCurrentJob)->mResult = 0xd;
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
            ((EA::Internet::Job_s0094_2290*)wti->mpCurrentJob)->mResult = 0xd;
            total = -1;
            break;
        }
        if (wti->mbCancelCurrent != 0 || wti->mbShouldQuit != 0) break;
    }
    ((EA::Internet::Job_s0094_2290*)wti->mpCurrentJob)->mnLastNotifySize = (unsigned __int64)total;
    return total;
}

// 0x00942050 / 0x009420E0 are members of the *response* object that the HTTPClient job
// holds; ReadResponseBody calls them with `this = job->mpResponse + 0x4a4`.
struct HTTPResponseHdr_s0094_2290 {
    bool FindHeader(const char* name, void** out, int index);       // 00942050
    bool FindHeaderByField(int field, void** out, int index);       // 009420E0
};

// @ 0x00942b40
bool EA::Internet::HTTPClient_s0094_2290::ReadResponseBody(EA::Internet::WorkerThreadInfo_s0094_2290* wti)
{
    EA::Internet::Job_s0094_2290* job = (EA::Internet::Job_s0094_2290*)wti->mpCurrentJob;
    if (*(int*)((char*)job->mpRequest + 0x2c) == 3) return true;
    if (*(int*)((char*)job->mpResponse + 0xf3c) == 0) { job->mResult = 0xb; return false; }

    __int64 len = 0;
    bool chunked = false;
    void* outptr[2];
    HTTPResponseHdr_s0094_2290* hdr = (HTTPResponseHdr_s0094_2290*)((char*)job->mpResponse + 0x4a4);
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
        job = (EA::Internet::Job_s0094_2290*)wti->mpCurrentJob;
        job->mnLastNotifySize = 0;
        __int64 r;
        if (chunked) r = ReadChunkedResponseData(wti);
        else        r = ReadResponseData(wti, (unsigned)len, (unsigned)(len >> 32), 1);
        if (wti->mbCancelCurrent == 0 && wti->mbShouldQuit == 0 && r < 0) return false;
    }
    return true;
}

// @ 0x00942ce0
// Cookie40 copy constructor (implicit): the forcing function below makes the compiler emit it out of line
#pragma auto_inline(off)
void rwForceEmit_Cookie40_copy(const Cookie40& s)
{
    Cookie40 c(s);
}
#pragma auto_inline(on)

// @ 0x00942d70
// Cookie40 copy assignment (implicit): the forcing function below makes the compiler emit it out of line
#pragma auto_inline(off)
void rwForceEmit_Cookie40_assign(Cookie40& d, const Cookie40& s)
{
    d = s;
}
#pragma auto_inline(on)

// @ 0x00942e50
void eastl::StrStub::assignRange(const char* first, const char* last)
{
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

// @ 0x00942f70
void UrlHolder::SetURL(const char* url)
{
    mUrl.SetURL(url, 1);
    void* p1 = mUrl.GetAccessor();
    int v1 = *(int*)((char*)p1 + 4);
    void* p2 = mUrl.GetAccessor();
    int v2 = *(int*)p2;
    mString.assign((const char*)v2, (const char*)v1);
}

// @ 0x00942fb0
void EA::Internet::HTTPClient::SetUserAgent(char const * p)
{
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

// @ 0x00942ff0
bool ReportClient::ConnectToServer(WorkerInfo* wti)
{
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

// @ 0x00943420
void __stdcall JobDestroyRange(Job* first, Job* last)
{
    for (; first < last; first = (Job*)((char*)first + 0xa8)) {
        char* b = first->second.mpBegin;
        if ((int)(first->second.mpCapacity - b) > 1 && b != 0 && b != first->second.mpSelf)
            operator_delete__(b);
        char* a = first->first.mpBegin;
        if ((int)(first->first.mpCapacity - a) > 1 && a != 0 && a != first->first.mpSelf)
            operator_delete__(a);
    }
}

// @ 0x00943480
void __fastcall ListDestroy(CookieNode* head)
{
    CookieNode* n = head->mpNext;
    while (n != head) {
        CookieNode* next = n->mpNext;
        ReleaseRefObj(n->mData.mp24);
        ReleaseRefObj(n->mData.mp1c);
        operator_delete__(n);
        n = next;
    }
}

// @ 0x00943500
Job* JobDestroyRangeDst(Job* first, Job* last, Job* dst)
{
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

// @ 0x00943570
eastl::StrStub_s0094_2ff0* eastl::StrStub_s0094_2ff0::assign(const char* s)
{
    if (mpBegin != s) {
        if (mpBegin != mpEnd) {
            *mpBegin = 0;
            mpEnd = mpBegin;
        }
        assignRange(s, s + strlen(s));
    }
    return this;
}

// @ 0x009435b0
void CookieList::insertAtNext(const Cookie40_s0094_2ff0& src)
{
    InsertBefore(mpNode, src);
}

// @ 0x00943600
void CookieNode::insertBeforeSelf(const Cookie40_s0094_2ff0& src)
{
    InsertBefore(this, src);
}

// @ 0x00943650
Job::Job(const Job& s)
: first(s.first), second(s.second) {}

// @ 0x009436b0
Job& Job::operator=(const Job& s)
{
    first = s.first;
    second = s.second;
    return *this;
}

// @ 0x00943710
Job* UninitializedCopyJob(Job* first, Job* last, Job* dst)
{
    if (first != last) {
        do {
            new (dst) Job(*first);
            first = (Job*)((char*)first + 0xa8);
            dst = (Job*)((char*)dst + 0xa8);
        } while (first != last);
    }
    return dst;
}

// @ 0x009437a0
Job* CopyJob(Job* first, Job* last, Job* dst)
{
    for (; first != last; dst = (Job*)((char*)dst + 0xa8), first = (Job*)((char*)first + 0xa8))
        *dst = *first;
    return dst;
}

// @ 0x00943830
Job* CopyBackwardJob(Job* first, Job* last, Job* dst)
{
    while (last != first) {
        last = (Job*)((char*)last - 0xa8);
        dst = (Job*)((char*)dst - 0xa8);
        *dst = *last;
    }
    return dst;
}

// @ 0x009438c0
void HTTPRequest::SetMethod(int method)
{
    *(int*)((char*)this + 0x2c) = method;
    ((eastl::StrStub_s0094_2ff0*)((char*)this + 8))->assign(HTTPMethodToString(method));
}

// @ 0x00943910
bool ReportClient::CancelJob(unsigned id)
{
    mMutex.Lock(&kTimeoutForever);
    for (CookieNode* n = mJobList.mpNext; n != (CookieNode*)&mJobList; n = n->mpNext) {
        Cookie40_s0094_2ff0* job = &n->mData;
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

// @ 0x00943a30
bool ReportClient::CancelAllJobs(bool bWait, unsigned timeout)
{
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
            Cookie40_s0094_2ff0* job = &n->mData;
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

// @ 0x00943bd0
int HTTPClient_s0094_2ff0::ParseResponseStatus(WorkerThreadInfo* wti)
{
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
    ((eastl::StrStub_s0094_2ff0*)((char*)req + 0x440))->assign(mpReadBuffer + 0xd);
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

// @ 0x00943d70
bool CellHolder::AddCell(CellData* p)
{
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

// @ 0x00943de0
HTTPRequest::HTTPRequest()
{
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

// @ 0x00943ea0
HTTPRequest::~HTTPRequest()
{
    if (mp3cf != 0)
        (*(void(__thiscall**)(void*))((*(void***)mp3cf)[2]))(mp3cf);
    mJobs.destroyRange();
    mStr440.destroy();
    mStr21c.destroy();
    mStr08.destroy();
    *(void**)this = (void*)0x13fb19c;
}

// @ 0x009440e0
namespace EA { namespace Internet {
bool HTTPClient_s0094_3f60::Shutdown()
{
    if (mbInitialized) {
        mMutex.Lock(&kLockTimeout);
        if (mpNotify) {
            mpNotify(mpNotifyCtx, this, 0x700af201, 0, 0);
            mpNotify = 0;
        }
        mpNotifyCtx = 0;
        if (mpLogB) {
            if (VCALLI0(mpLogB, 0x10)) {
                VCALL0(mpLogB, 0x34);
                VCALL0(mpLogB, 0x18);
            }
            VCALL0(mpLogB, 0x08);
        }
        if (mpLogA) {
            // The original calls the B stream's 0x34/0x18 slots here (retail copy-paste).
            if (VCALLI0(mpLogA, 0x10)) {
                VCALL0(mpLogB, 0x34);
                VCALL0(mpLogB, 0x18);
            }
            VCALL0(mpLogA, 0x08);
        }
        WorkerThreadInfo_s0094_3f60* info = mpWorkerThreadInfo;
        if (info && info->bCreated) {
            VCALL0(info->mpSocket, 0x00);
            SetTimeout(0, 0);
            Pump(info->mpSocket);
            VCALL0(info->mpSocket, 0x04);
        }
        operator_delete__(mpReadBuffer);
        if (mpWriteBuffer)
            operator_delete__(mpWriteBuffer);
        mbInitialized = false;
        mMutex.Unlock();
    }
    while (mpFiltersBegin != mpFiltersEnd) {
        RefObj_s0094_3f60* p = *--mpFiltersEnd;
        int old = _InterlockedExchangeAdd((volatile long*)&p->mnRefCount, -1);
        if (old - 1 == 0) {
            _InterlockedExchange((volatile long*)&p->mnRefCount, 1);
            if (p)
                p->Destroy(1);
        }
    }
    return true;
}
}}  // namespace EA::Internet

// @ 0x00944f40
bool HTTPClient_s0094_4f40::Fn944f40(Info* info)
{
    Job_s0094_4f40* job = info->mpCurrentJob;
    Req* req = job->mpRequest;
    HeaderList_s0094_4f40* hdr = req->headers();

    const char* userAgentField = HeaderFieldToFieldString(0x18);
    if (!hdr->FindHeader(userAgentField, 0, 0)) {
        if (msUserAgent.mpBegin != msUserAgent.mpEnd)
            hdr->AddHeaderPtr(0x18, &msUserAgent);
    }

    FStr s;
    s.Init();
    s.append(req->msMethod.mpBegin, CharStrEnd_s0094_4f40(req->msMethod.mpBegin));
    s.append(' ');

    if (msProxyServerAddress.mpBegin != msProxyServerAddress.mpEnd) {
        hdr->SetHeaderId(HeaderFieldToFieldString(0xe), 0);
        s.Append("http://");
        Str* part = req->url()->GetPart(3);
        s.append(part->mpBegin, CharStrEnd_s0094_4f40(part->mpBegin));
        int port = req->url()->GetPort();
        if (port != 0) {
            char buf[20];
            _ultoa(port, buf, 10);
            s.append(':');
            s.append(buf, CharStrEnd_s0094_4f40(buf));
        }
    } else {
        const char* proxyField = HeaderFieldToFieldString(0xe);
        if (!hdr->FindHeader(proxyField, 0, 0)) {
            Str* part = req->url()->GetPart(4);
            if (part->mpBegin != part->mpEnd) {
                Str tmp;
                tmp.mpBegin = 0;
                tmp.mpEnd = 0;
                tmp.mpCapacity = 0;
                tmp.assign(part->mpBegin);
                tmp.assignRange((const char*)0x013fe618, (const char*)0x013fe619);
                tmp.assignRange(part->mpBegin, CharStrEnd_s0094_4f40(part->mpBegin));
                hdr->AddHeaderStr(0xe, tmp.mpBegin);
                if ((tmp.mpEnd - tmp.mpBegin) > 1 && tmp.mpBegin && tmp.mpBegin != (char*)&tmp)
                    operator_delete__(tmp.mpBegin);
            } else {
                req->url()->GetPart(4);
                hdr->AddHeaderPtr(0xe, 0);
            }
        }
        if (req->mnField2c == 1)
            s.append('*');
    }

    if (req->mnField2c != 1) {
        Str* p;
        p = req->url()->GetPart(5); s.append(p->mpBegin, CharStrEnd_s0094_4f40(p->mpBegin));
        p = req->url()->GetPart(6); s.append(p->mpBegin, CharStrEnd_s0094_4f40(p->mpBegin));
        p = req->url()->GetPart(7); s.append(p->mpBegin, CharStrEnd_s0094_4f40(p->mpBegin));
        p = req->url()->GetPart(8); s.append(p->mpBegin, CharStrEnd_s0094_4f40(p->mpBegin));
    }
    s.append((const char*)0x0143f274, (const char*)0x0143f27f);

    if (!ReadRawBody(info, s.mpBegin)) {
        if ((s.mpEnd - s.mpBegin) > 1 && s.mpBegin && s.mpBegin != s.mpField10)
            operator_delete__(s.mpBegin);
        return false;
    }

    HeaderNode* node = hdr->mpBegin;
    HeaderNode* end = hdr->mpEnd;
    while (node != end) {
        if (info->mbCancelCurrent || info->mbShouldQuit) {
            if ((s.mpEnd - s.mpBegin) > 1 && s.mpBegin && s.mpBegin != s.mpField10)
                operator_delete__(s.mpBegin);
            return true;
        }
        if (s.mpBegin != node->msName.mpBegin) {
            if (s.mpBegin != s.mpCapacity) {
                *s.mpBegin = 0;
                s.mpCapacity = s.mpBegin;
            }
            s.append(node->msName.mpBegin, CharStrEnd_s0094_4f40(node->msName.mpBegin));
        }
        s.append((const char*)0x01420a80, (const char*)0x01420a82);
        s.append(node->msValue.mpBegin, CharStrEnd_s0094_4f40(node->msValue.mpBegin));
        s.append((const char*)0x013fb750, (const char*)0x013fb752);
        if (!ReadRawBody(info, s.mpBegin))
            break;
        node = (HeaderNode*)((char*)node + 0xa8);
    }

    bool ok = ReadRawBody(info, (char*)0x013fb750) != 0;
    if ((s.mpEnd - s.mpBegin) > 1 && s.mpBegin && s.mpBegin != s.mpField10)
        operator_delete__(s.mpBegin);
    return ok;
}

// @ 0x009453f0
bool HTTPClient_s0094_4f40::Fn9453f0(Info* info)
{
    Resp* resp = info->mpCurrentJob->mpResponse;
    if (!ParseResponseStatus(info))
        return false;

    Str name;
    name.mpBegin = 0;
    name.mpEnd = 0;
    name.mpCapacity = 0;
    Str value;
    value.mpBegin = 0;
    value.mpEnd = 0;
    value.mpCapacity = 0;
    bool firstField = true;
    bool haveName = false;
    int consumed = 0;

    for (;;) {
        if (consumed != 0) {
            mpReadBuffer[0] = mpReadBuffer[mnReadBufferSize - 2];
            mpReadBuffer[1] = mpReadBuffer[mnReadBufferSize - 1];
        }
        int n = ReadResponseLine(info, mpReadBuffer + consumed, (int)mnReadBufferSize - consumed - 2, 0);
        if (n < 0) {
            if (name.mpBegin) operator_delete__(name.mpBegin);
            if (value.mpBegin) operator_delete__(value.mpBegin);
            return false;
        }
        n += consumed;
        if (n == (int)mnReadBufferSize - 2 && mpReadBuffer[n - 1] != '\n') {
            consumed = ReadResponseLine(info, mpReadBuffer + n, 2, 0);
            if (consumed < 0) {
                if (name.mpBegin) operator_delete__(name.mpBegin);
                if (value.mpBegin) operator_delete__(value.mpBegin);
                return false;
            }
            n += consumed;
        } else {
            consumed = 0;
        }

        int lineLen = n;
        while (lineLen > 0 && (mpReadBuffer[lineLen - 1] == '\n' || mpReadBuffer[lineLen - 1] == '\r'))
            --lineLen;

        if (lineLen == 0) {
            if (haveName) {
                HeaderList_s0094_4f40* list = resp->headers4a4();
                list->AddNode();
                HeaderNode* node = list->mpEnd - 1;
                node->msName.assignRange(name.mpBegin, CharStrEnd_s0094_4f40(name.mpBegin));
                node->msValue.assignRange(value.mpBegin, CharStrEnd_s0094_4f40(value.mpBegin));
                haveName = false;
            }
        } else if (firstField && mpReadBuffer[0] != ' ' && mpReadBuffer[0] != '\t') {
            if (haveName) {
                HeaderList_s0094_4f40* list = resp->headers4a4();
                list->AddNode();
                HeaderNode* node = list->mpEnd - 1;
                node->msName.assignRange(name.mpBegin, CharStrEnd_s0094_4f40(name.mpBegin));
                node->msValue.assignRange(value.mpBegin, CharStrEnd_s0094_4f40(value.mpBegin));
                haveName = false;
            }
            StrClear(name);
            StrClear(value);
            int i = 0;
            while (i < lineLen && mpReadBuffer[i] != ':')
                ++i;
            name.assignRange(mpReadBuffer, mpReadBuffer + i);
            haveName = true;
            if (i < lineLen)
                value.assignRange(mpReadBuffer + i + 1, mpReadBuffer + lineLen);
        } else {
            int i = 0;
            while (i < lineLen && (mpReadBuffer[i] == ' ' || mpReadBuffer[i] == '\t'))
                ++i;
            value.append(mpReadBuffer + i, mpReadBuffer + lineLen);
        }
        firstField = false;
        if (lineLen == 0 || info->mbCancelCurrent || info->mbShouldQuit) {
            if (name.mpBegin) operator_delete__(name.mpBegin);
            if (value.mpBegin) operator_delete__(value.mpBegin);
            return true;
        }
    }
}

// @ 0x009458c0
bool HTTPClient_s0094_4f40::Fn9458c0(Job_s0094_4f40* job)
{
    Resp* resp = job->mpResponse;
    Req* req = job->mpRequest;

    if (resp == 0)
        return false;
    if (job->mnRedirectionCount >= 5)
        return false;

    const char* loc = 0;
    if (!resp->headers4a4()->FindHeader(HeaderFieldToFieldString(0x1a), &loc, 0))
        return false;

    ++job->mnRedirectionCount;
    if (Fn94ba30(loc)) {
        Str s;
        s.mpBegin = 0;
        s.mpEnd = 0;
        s.mpCapacity = 0;
        s.assign(GetPoliticalID((char*)req + 0x30));
        req->url()->Fn94bb50(loc, s.mpBegin);
        if ((s.mpEnd - s.mpBegin) > 1 && s.mpBegin)
            operator_delete__(s.mpBegin);
    } else {
        req->url()->SetURL(loc, true);
    }

    if (req->mpStreamD8c != 0) {
        if (!((VF_B2)VS(req->mpStreamD8c, 0x28))(req->mpStreamD8c, 0, 0))
            return false;
    }
    if (req->mpStreamD90 != 0) {
        if (!((VF_B2)VS(req->mpStreamD90, 0x28))(req->mpStreamD90, 0, 0))
            return false;
        if (!((VF_B1)VS(req->mpStreamD90, 0x20))(req->mpStreamD90, 0))
            return false;
    }
    if (job->mpResponse != 0)
        job->mpResponse->Clear();
    job->mnField10 = 1;
    job->mnField14 = 0;
    job->mResult = 1;
    mMutex.Lock(0x0143f214);
    cookieList()->insertAtNext(job);
    mMutex.Unlock();
    return true;
}

// @ 0x00945a10
int HTTPClient_s0094_4f40::Fn945a10(Info* info)
{
    Job_s0094_4f40* job = info->mpCurrentJob;
    int code = job->mpResponse->mnStatus;
    int method = job->mpRequest->mnField2c;

    if (method == 1 || method == 6 || method == 7)
        goto redirect;

    if (method == 2 || method == 3) {
        if ((unsigned)(code - 200) <= 99) {
            job->mResult = 0;
            return 0;
        }
        goto retryOrFail;
    }

    if (method != 4 && method != 5)
        goto redirect;

    if ((unsigned)(code - 200) <= 99) {
        job->mResult = 0;
        return 0;
    }
    if ((unsigned)(code - 300) > 99)
        goto giveUp;
    if (method == 4)
        goto retryOrFail;
    goto giveUp;

retryOrFail:
    if (code <= 0x12f) {
        if (Fn9458c0(job))
            return 1;
    }
    job->mResult = 9;
    return 0;

redirect:
    job->mResult = ((unsigned)(code - 200) > 99) ? 9 : 0;
    return 0;

giveUp:
    job->mResult = (code == 0x191) ? 10 : 9;
    return 0;
}

// @ 0x00945b20
bool HTTPRequest_s0094_4f40::CreateHTTPPostRequest(const char* url, void* body, void* image, Req** out)
{
    if (out == 0 || body == 0)
        return false;
    if (!((VF_B0)VS(body, 0x44))(body))
        return false;

    Req* req = (Req*)operator_new(0xd98, "UTFInternet/HTTPRequest", 0, 0, 0, 0);
    if (req)
        req = (Req*)req->ctor();
    else
        req = 0;
    if (req)
        ++req->mnRefCount;
    ++req->mnRefCount;

    req->SetMethod(4);
    req->SetURL(url);
    req->Fn615c10(image);
    req->Fn615bd0(body);

    int n = ((VF_I0)VS(body, 0x2c))(body);
    if (n == -1) {
        AtomicRefRelease(&req);
        return false;
    }

    char buf[64];
    Sprintf8_s0094_4f40(buf, (const char*)0x013fc740, n);
    req->headers()->AddHeaderStr(0x26, buf);

    Str s;
    s.mpBegin = (char*)0x01667bac;
    s.mpEnd = (char*)0x01667bac;
    s.mpCapacity = (char*)0x01667bad;

    if (!((VF_BS)VS(body, 0x40))(body, &s)) {
        StrDtor(&s);
        AtomicRefRelease(&req);
        return false;
    }

    req->headers()->AddHeaderPtr(0x2a, &s);
    *out = req;
    StrDtor(&s);
    AtomicRefRelease(&req);
    return true;
}

// @ 0x00945c80
bool HTTPClient_s0094_4f40::WriteRequestBody(Info* info)
{
    Job_s0094_4f40* job = info->mpCurrentJob;
    int timeout = 0;

    if (mpWriteBuffer == 0)
        mpWriteBuffer = (char*)operator_new(mnWriteBufferSize, "UTFInternet/char8_t", 0, 0, 0, 0);

    switch (job->mpRequest->mnField2c) {
    case 1: case 2: case 3: case 6: case 7: case 9: case 10:
        job->mResult = 3;
        return false;
    }

    job->mnUploadBodySize = 0;

    void* stream = job->mpRequest->mpStreamD8c;
    int remaining = ((VF_I0)VS(stream, 0x2c))(stream);
    int chunk = 0;
    unsigned offset = 0;

    for (;;) {
        if (remaining == 0 || info->mbCancelCurrent || info->mbShouldQuit)
            return true;
        if (HTTPClientCheckTimeout((int)(size_t)job, &timeout)) {
            job->mResult = 6;
            return false;
        }

        void* opts = ((VF_This0)VS(info->mpSocket, 0x10))(info->mpSocket);
        if (((VF_B1)VS(opts, 0x64))(opts, 0)) {
            if (!Fn9453f0(info)) {
                job->mResult = 3;
                return false;
            }
            int status = job->mpResponse->mnStatus;
            if (status <= 100 || status >= 199)
                return true;
            job->mpResponse->Clear();
        }

        opts = ((VF_This0)VS(info->mpSocket, 0x10))(info->mpSocket);
        if (((VF_B1)VS(opts, 0x68))(opts, 1000) == 0 &&
            ((VF_I0)VS(info->mpSocket, 0x2c))(info->mpSocket) == 2)
            goto next;

        if (chunk == 0) {
            chunk = ((VF_I2)VS(stream, 0x30))(stream, mpWriteBuffer, (int)mnWriteBufferSize);
            offset = 0;
            if (chunk < 1) {
                job->mResult = 0xc;
                return false;
            }
        }

        {
            int n = ((VF_I3)VS(info->mpSocket, 0x48))(info->mpSocket, mpWriteBuffer + offset, chunk, 0);
            if (n < 0) {
                job->mResult = 7;
                return false;
            }
            HTTPClientSendCallback(n, mpWriteBuffer + offset, 0);
            offset += n;
            chunk -= n;
            job->mnUploadBodySize += n;
            mnBytesSent += n;
        }
    next:
        remaining = ((VF_I0)VS(stream, 0x2c))(stream);
    }
}

// @ 0x00945ed0
namespace EA { namespace Internet {
unsigned HTTPClient_s0094_5ed0::WorkerThreadFunction(WorkerThreadInfo_s0094_5ed0* info)
{
    Job_s0094_5ed0 job;
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
            ReleaseRefObj_s0094_5ed0((RefObj_s0094_5ed0*)node->job.mpResponse.mp);
            ReleaseRefObj_s0094_5ed0((RefObj_s0094_5ed0*)node->job.mpRequest.mp);
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
            eastl::StrStub_s0094_5ed0& body = job.mpResponse.mp->msBody;
            if (body.mpBegin != url) {
                if (body.mpBegin != body.mpEnd) {
                    *body.mpBegin = 0;
                    body.mpEnd = body.mpBegin;
                }
                body.appendFixed(url, CharStrEnd(url));
            }
        }
        {
            eastl::StrStub_s0094_5ed0* dst = &job.mpResponse.mp->msStr21c;
            eastl::StrStub_s0094_5ed0* src = &job.mpRequest.mp->msStrE0;
            if (dst != src) {
                if (dst->mpBegin != dst->mpEnd) {
                    *dst->mpBegin = 0;
                    dst->mpEnd = dst->mpBegin;
                }
                dst->appendFixed(src->mpBegin, src->mpEnd);
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
            HTTPResponse_s0094_5ed0* r = job.mpResponse.mp;
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
}}  // namespace EA::Internet

// @ 0x00946520
namespace EA { namespace Internet {
unsigned HTTPClient_s0094_5ed0::StaticWorkerThreadFunction(WorkerThreadInfo_s0094_5ed0* info)
{
    HTTPClient_s0094_5ed0* c = info->mpOwner;
    unsigned r = c->WorkerThreadFunction(info);
    c->Release();
    return r;
}
}}  // namespace EA::Internet

// @ 0x00946540
namespace EA { namespace Internet {
void HTTPClient_s0094_5ed0::CreateWorkerThreadIfNeeded()
{
    mMutex.Lock(&kLockTimeout);
    if (mpWorkerThreadInfo == 0) {
        WorkerThreadInfo_s0094_5ed0* p = new("UTFInternet/WorkerThreadInfo", 0, 0, 0, 0) WorkerThreadInfo_s0094_5ed0;
        mpWorkerThreadInfo = p;
        HTTPClient_s0094_5ed0* old = p->mpOwner;
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
        WorkerThreadInfo_s0094_5ed0* info = mpWorkerThreadInfo;
        info->mThread.Begin((void*)StaticWorkerThreadFunction, info, 0, GetThreadPriorityDefault());
    }
    mMutex.Unlock();
}
}}  // namespace EA::Internet

// @ 0x00946680
namespace EA { namespace Internet {
unsigned HTTPClient_s0094_5ed0::AddNewJob(HTTPRequestStub* req, int arg3, bool arg4, int arg5)
{
    if (!mbInitialized)
        return 0;
    if (req == 0 || !(req->mpUrlEnd - req->mpUrlBegin))
        return 0;
    eastl::StrStub_s0094_5ed0* host = req->urlHolder.GetString();
    if (host->mpBegin == host->mpEnd)
        return 0;
    Job_s0094_5ed0 job;
    job.state = 1;
    job.userData = arg5;
    job.z0 = 0;
    job.one = 1;
    job.z2 = 0;
    job.z1 = 0;
    job.mpRequest.Set(req);
    job.bFlag = arg4;
    job.mpResponse.Set(new("UTFInternet/WorkerThreadInfo", 0, 0, 0, 0) HTTPResponse_s0094_5ed0);
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
}}  // namespace EA::Internet
