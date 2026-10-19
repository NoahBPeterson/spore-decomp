// src/game/UTFSpore_Win32/HTTPHandler.cpp -- migrated from slice(s) s008fd6c0, s008fc670 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/HTTPHandler.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/IO/FileStream.h"

// unnamed retail callees and globals (address in the comment)
extern "C" unsigned __cdecl strlen(const char* s);
extern "C" void* __cdecl memcpy(void*, const void*, unsigned);
extern char gEmptyStr[2];                  // 0x01667bac
extern const char kUserAgent[31];   // 0x01439e20
extern const float kDefLMRatio;     // 0x013ec480
extern "C" int __cdecl strcmp(const char*, const char*);
#include <intrin.h>
#include "EA/Internet/INetFileCache.h"
#include "EA/Internet/HTTPClient.h"
#include "EA/Internet/HTTPRequest.h"
#pragma function(memcpy)
#pragma intrinsic(strcmp)

// ---- items of slice s008fc670 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" unsigned __cdecl strlen(const char* s);
struct RCObj {
    virtual void v0(int);
    int rc;
};
inline void RCAddRef(RCObj* p)
{
    if (p)
        _InterlockedIncrement((volatile long*)((char*)p + 4));
}
inline void RCRelease(RCObj* p)
{
    if (p) {
        if (_InterlockedDecrement((volatile long*)((char*)p + 4)) == 0) {
            _InterlockedExchange((volatile long*)((char*)p + 4), 1);
            if (p)
                p->v0(1);
        }
    }
}
struct AutoRef {
    RCObj* mp;
    AutoRef* operator=(RCObj* p);
};
unsigned __cdecl FnvHash(const char* s, unsigned h, int a);
struct EStr {
    char* mpBegin;      // +0
    char* mpEnd;        // +4
    void assign(const char* first, const char* last);
};
struct HTTPy {
    char pad0[0x17c];
    EStr mEnc;          // +0x17c
    void SetAcceptEncoding(const char* s);
};
struct BaseA2 { virtual void a(); ~BaseA2() {} };
struct BaseB2 {
    virtual void b();
    int m4;
    BaseB2() { m4 = 0; }
    ~BaseB2() {}
};
struct D290 : BaseA2, BaseB2 {
    int m0c, m10, m14, m18;
    uint8_t m1c;
    __declspec(noinline) D290(int x);
};
struct LogFilter {
    void AddRef();              // 0x93c3e0
    void Release();             // 0x949d90
    unsigned GetLevelMask();    // 0x989360
};
struct LogFilterPtr {        // eastl/EA AutoRefCount<LogFilter>
    LogFilter* mp;
    LogFilterPtr& operator=(LogFilter* p) {
        if (p != mp) {
            LogFilter* old = mp;
            if (p)
                p->AddRef();
            mp = p;
            if (old)
                old->Release();
        }
        return *this;
    }
};
struct HTTPz {
    char pad0[0x1cc];
    int m1cc;               // +0x1cc
    char pad1d0[0x1d8 - 0x1d0];
    LogFilterPtr m1d8;      // +0x1d8
    void SetFilter(LogFilter* p, unsigned mask);
};
extern "C" void* __cdecl memcpy(void*, const void*, unsigned);
void __cdecl operator_delete__(void*);
struct MsgObj { virtual void v0(int); virtual void v1(); virtual void v2(); };
struct MsgServer {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4(); virtual void s5();
    virtual void Post(unsigned id, MsgObj* o, int a, int b);        // +0x18
    virtual void s7(); virtual void s8();
    virtual void Register(void* h, unsigned id);                    // +0x24
    virtual void s10();
    virtual void Unregister(void* h, unsigned id, int pri);         // +0x2c
};
MsgServer* __cdecl GetServer();
extern char gEmptyStr[2];                  // 0x01667bac
struct EStr16 {
    char* b; char* e; char* c; int al;
    void RangeInit(unsigned n);                                     // 0x00475ab0 eastl RangeInitialize (thiscall)
    EStr16()
    {
        b = gEmptyStr;
        e = gEmptyStr;
        c = gEmptyStr + 1;
    }
    EStr16(const char* p, unsigned n)
    {
        b = 0;
        e = 0;
        c = 0;
        RangeInit(n + 1);
        char* d = b;
        memcpy(d, p, n);
        e = d + n;
        *e = 0;
    }
};
struct HClientV {
    virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4();
    virtual void c5();
};
struct HClient {
    unsigned raw[0x168 / 4];
    HClientV* v() { return (HClientV*)this; }
    HClient();      // 0x00943f60
};
void __fastcall HClientDtor(HClient*);
struct HMsg {
    int pad0; int f4; char pad1[0x14]; RCObj* f1c; char pad2[4]; RCObj* f24; MsgObj* f28;
};
struct IProtocolHandler {
    int rc;             // +4
    int prov;           // +8
    IProtocolHandler() : rc(0), prov(0) {}
    virtual ~IProtocolHandler() {}
    virtual void ph1();
};
struct IMsgHandler {
    IMsgHandler() {}
    virtual ~IMsgHandler() {}
    virtual void mh1();
};
struct HttpHandler : IProtocolHandler, IMsgHandler {
    HClient client;     // +0x10
    bool inited;        // +0x178
    EStr16 ua;          // +0x17c
    EStr16 accept;      // +0x18c
    EStr16 charset;     // +0x19c
    EStr16 enc;         // +0x1ac
    EStr16 lang;        // +0x1bc
    int m1cc;           // +0x1cc
    uint8_t mb1d0;      // +0x1d0
    float mf1d4;        // +0x1d4
    void* cache;        // +0x1d8
    RCObj* auth;        // +0x1dc
    void* m1e0;         // +0x1e0
    int m1e4, m1e8;
    HttpHandler();
    virtual ~HttpHandler();
};
inline void RelNA(RCObj* p)
{
    if (p) {
        int n = (*(volatile int*)&p->rc += -1);
        if (n == 0) {
            *(volatile int*)&p->rc = 1;
            _ReadWriteBarrier();
            p->v0(1);
        }
    }
}
inline void StrFree(EStr16& s)
{
    if (s.c - s.b > 1 && s.b)
        operator_delete__(s.b);
}
void __fastcall CacheRelease(void* p);
extern const char kUserAgent[31];   // 0x01439e20
extern const float kDefLMRatio;     // 0x013ec480
// ---- items of slice s008fc670 end

// ---- items of slice s008fd6c0 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) char* __cdecl strstr(const char* s, const char* sub);
extern "C" __declspec(dllimport) char* __cdecl strpbrk(const char*, const char*);
extern "C" __declspec(dllimport) long __cdecl strtol(const char*, char**, int);
extern wchar_t gEmptyWStr[2];  // 0x1667bac (same empty-string object as gEmptyStr)
#pragma intrinsic(strlen)
unsigned __cdecl EncodingFromName(const char* name);   // 0x8fd0a0
struct HTTPlang {
    char pad0[0x1bc];
    EStr mLang;             // +0x1bc
    void SetAcceptLanguage(const char* s);
};
struct ReqListener {
    virtual void l0();
    virtual void Report(unsigned code, const wchar_t* url, int a, int b, const wchar_t* msg);   // +4
};
struct IStreamLike;
struct ResourceRequest {
    char pad0[8];
    ReqListener* mpListener;    // +8
    const wchar_t* mUrl;        // +0xc
    EStr mType;                 // +0x10
    char pad18[0x2c - 0x18];
    bool mb2c;                  // +0x2c
    char pad2d[0x38 - 0x2d];
    unsigned mKey;              // +0x38
    void SetEncoding(unsigned enc, int a);   // 0x9002f0
    void SetStream(IStreamLike* s);     // 0x836480
};
void* __cdecl operator_new(unsigned size, const char* name, int a, int b, const char* file, int line);
void* __cdecl operator_new(unsigned size, const char* name, int a, int b, int c, int d);
inline void* operator new(unsigned size, const char* name, int a, int b, int c, int d)
{
    return operator_new(size, name, a, b, c, d);
}
const char* __cdecl StrIStr(const char* hay, const char* needle);      // 0x92cc00
struct IUnk {
    virtual void d0(int);
    virtual void AddRef();          // +4
    virtual void Release();         // +8
};
struct UnkRef {                     // intrusive_ptr-style holder
    IUnk* p;
    UnkRef() : p(0) {}
    ~UnkRef() { if (p) p->Release(); }
};
struct HeaderSet {
    bool FindHeader(int field, const char** out, int index);                // 0x9420e0
    void SetHeader(int field, const void* str);                            // 0x944d50
};
struct NStrBase { char* b; char* e; char* c; int al; };
struct NStrI : NStrBase {                       // fully inline
    __forceinline NStrI(const char* pBegin)
    {
        b = 0;
        e = 0;
        c = 0;
        const char* pEnd = pBegin + strlen(pBegin);
        unsigned n = (unsigned)(pEnd - pBegin);
        unsigned cap = n + 1;
        char* d;
        if (cap > 1) {
            d = (char*)operator_new(cap, "EASTL", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
            c = d + cap;
        } else {
            d = gEmptyStr;
            c = gEmptyStr + 1;
        }
        b = d;
        e = d;
        memcpy(d, pBegin, n);
        e = (char*)((d - pBegin) + pEnd);
        *e = 0;
    }
    ~NStrI()
    {
        if (c - b > 1 && b)
            operator_delete__(b);
    }
};
struct NStrD : NStrBase {                       // inline ctor, out-of-line dtor
    __forceinline NStrD(const char* pBegin)
    {
        b = 0;
        e = 0;
        c = 0;
        const char* pEnd = pBegin + strlen(pBegin);
        unsigned n = (unsigned)(pEnd - pBegin);
        unsigned cap = n + 1;
        char* d;
        if (cap > 1) {
            d = (char*)operator_new(cap, "EASTL", 0, 0,
                "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h", 0xd1);
            c = d + cap;
        } else {
            d = gEmptyStr;
            c = gEmptyStr + 1;
        }
        b = d;
        e = d;
        memcpy(d, pBegin, n);
        e = (char*)((d - pBegin) + pEnd);
        *e = 0;
    }
    ~NStrD();                                   // 0x530670
};
struct NStrAlloc { char c; };
struct NStrX : NStrBase {                       // ctor and dtor both out of line
    NStrX(const char* p, const NStrAlloc& a);   // 0x57ed80
    ~NStrX();                                   // 0x530670
};
unsigned __cdecl ParseHttpDate(NStrBase* s);    // 0x947cd0
struct CtorSprintf { char c; CtorSprintf() { c = 0; } };
struct NStrS : NStrBase {                       // sprintf constructed
    NStrS(CtorSprintf, const char* fmt, ...);   // 0x472f50
    ~NStrS()
    {
        if (c - b > 1 && b)
            operator_delete__(b);
    }
};
struct NStrE : NStrBase {                       // default constructed + member sprintf
    NStrE()
    {
        b = gEmptyStr;
        e = gEmptyStr;
        c = gEmptyStr + 1;
    }
    void sprintf(const char* fmt, ...);         // 0x472fe0
    ~NStrE()
    {
        if (c - b > 1 && b)
            operator_delete__(b);
    }
};
struct WStrE {
    wchar_t* b; wchar_t* e; wchar_t* c; int al;
    WStrE()
    {
        b = gEmptyWStr;
        e = gEmptyWStr;
        c = gEmptyWStr + 2;
    }
    void sprintf(const wchar_t* fmt, ...);      // 0x41e050
    void DeallocateSelf();                      // 0x933960
    ~WStrE() { DeallocateSelf(); }
};
struct FileCache {
    bool Exists(const char* name);                                          // 0x948860
    void RemoveCachedData(const char* name);                                // 0x949530
    bool GetCachedDataStream(const char* name, IStreamLike** out, const char** mime);   // 0x9498c0
    bool CreateNewCachedDataStream(IUnk** out);                             // 0x9484e0
    void CommitNewCachedDataStream(void* stream, unsigned size, unsigned loc, int flag, const void* extra, int timeout);  // 0x949620
};
struct JobPair { unsigned first; unsigned second; };
JobPair* __cdecl LowerBoundJob(JobPair* first, JobPair* last, const unsigned* key, bool flag);   // 0x5701b0
__forceinline JobPair* CopyJobs(JobPair* first, JobPair* last, JobPair* result)
{
    for (; first != last; ++first, ++result) {
        result->first = first->first;
        result->second = first->second;
    }
    return result;
}
struct JobMap {
    JobPair* mpBegin;
    JobPair* mpEnd;
    JobPair* mpCapacity;
    int pad[2];
    bool mbFlag;                // +0x14
    char pad2[3];
    bool erase(const unsigned& key);                // 0x8fdca0
    JobPair* find(const unsigned& key)
    {
        JobPair* e = mpEnd;
        JobPair* it = LowerBoundJob(mpBegin, e, &key, mbFlag);
        if (it == e || key < it->first || it == it + 1)
            it = e;
        return it;
    }
    unsigned& operator[](const unsigned& key);      // 0x564a10
    void EraseRange(JobPair* first, JobPair* last); // 0x530c80
};
struct HttpResp {
    char pad0[0x21c];
    unsigned size;              // +0x21c
    char pad1[0x43c - 0x220];
    int code;                   // +0x43c
    const char* message;        // +0x440
    char pad2[0x4a4 - 0x444];
    HeaderSet hdrs;             // +0x4a4
    char pad3[0xf3c - 0x4a4 - 1];
    IUnk* stream;               // +0xf3c
};
struct JobSub {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7();
    virtual void Reset(int a, int b);                   // +0x20 slot index 8 is below
};
struct JobHolder {
    char pad[0xd8c];
    IUnk* sub1;                 // +0xd8c
    IUnk* sub2;                 // +0xd90
};
struct JobMsg {
    virtual void d0(int);
    virtual void AddRef();      // +4
    virtual void Release();     // +8
    int pad4;
    int pad8;
    int reqId;                  // +0xc
    int event;                  // +0x10
    JobHolder* job;             // +0x14
    HttpResp* resp;             // +0x18
    bool retried;               // +0x1c
};
struct HClientV2 {
    virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3(); virtual void c4();
    virtual void c5();
    void SetNotificationTarget(void (__cdecl* cb)(unsigned, unsigned, int, void*), int a);     // 0x942150
    void SetUserAgent(const char* s);                                       // 0x942fb0
    int AddNewJob(void* req, void* job, int a, int b);                      // 0x946680
    bool CancelJob(unsigned handle);                                        // 0x943910
};
struct HClient2 {
    unsigned raw[0x168 / 4];
    HClientV2* v() { return (HClientV2*)this; }
};
struct EStr16b { char* b; char* e; char* c; int al; };
struct RCAtomic { void* vt; int rc; };
struct AutoRefAtomic {
    RCAtomic* mp;
    ~AutoRefAtomic();                               // 0x60d210
};
struct MsgServer2 {
    virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3(); virtual void s4();
    virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8();
    virtual void Register(void* h, unsigned id);                    // +0x24
};
MsgServer2* __cdecl GetServer2();
void __cdecl HandlerMsgCb(unsigned a, unsigned b, int id, void* m);
struct ReqProvider {
    ResourceRequest* FindRequest(int id);                           // 0x8ff320
    void Complete(ResourceRequest* r, int status);                  // 0x8ffb40
};
struct AuthSvc {
    virtual void a0();
    virtual bool Authenticate(HttpResp* resp, void* job);           // +4
};
struct cJob {
    char data[0x20];                                // sizeof 0x20 (operator new size)
    cJob(unsigned key);                             // 0x8fd290
};
struct MemStream {
    virtual void d0(int);
    virtual void AddRef();                          // +4
    virtual void Release();                         // +8
    virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9();
    virtual void Open(int a, int b);                // +0x28
    char data[0x24 - 4];                            // sizeof 0x24 (operator new size)
    MemStream(const char* name);                    // 0x93bd50
    void SetProperty(int id, float v);              // 0x93bb40
};
struct HttpRequestObj {
    char pad[0x2f4];
    HeaderSet hdrs;                                 // +0x2f4
};
bool __cdecl CreateHTTPGetRequest(const char* url, IUnk* stream, HttpRequestObj** out);     // 0x944450
struct HttpHandler2 {
    void* vt0;                  // +0
    int rc;                     // +4
    ReqProvider* mpProvider;    // +8
    void* vt1;                  // +0xc
    HClient2 client;            // +0x10
    bool inited;                // +0x178
    EStr16b ua;                 // +0x17c
    EStr16b accept;             // +0x18c  (header id 8)
    EStr16b charset;            // +0x19c  (9)
    EStr16b enc;                // +0x1ac  (0xa)
    EStr16b lang;               // +0x1bc  (0xb)
    int m1cc;                   // +0x1cc  (cache commit location)
    bool mbUseLM;               // +0x1d0
    float mfLMRatio;            // +0x1d4
    FileCache* cache;           // +0x1d8
    AuthSvc* auth;              // +0x1dc
    JobMap jobs;                // +0x1e0

    long CalculateCacheTimeout(HeaderSet* hdrs);    // 0x8fd790
    bool NotificationTargetTest(const char* name);  // 0x8fdaf0
    bool CheckInit();                               // 0x8fdb70
    bool RemoveJobFor(ResourceRequest* r);          // 0x8fdc00
    bool ProcessRequest(ResourceRequest* req, bool bForce);     // 0x8fdd10
};
struct IMsgSub {    // the IMsgHandler subobject at HttpHandler+0xc
    bool HandleMessage(unsigned id, JobMsg* msg);               // 0x8fe0c0
};
// ---- items of slice s008fd6c0 end

// @ 0x008fd080
const wchar_t* __stdcall GetProtocolName(int i)
{
    if (i == 0)
        return L"http";
    return i == 1 ? L"https" : 0;
}

// @ 0x008fd0a0
namespace EA {
namespace XHTML {
namespace Resource {
unsigned int EncodingFromName(char const * name)
{
    uint32_t h = FnvHash(name, 0x811c9dc5, 1);
    switch (h) {
    case 0x510d43c2: return 0x3b6;
    case 0x209b0a7:  return 8;
    case 0x3730c93e: return 0x3a8;
    case 0x4d26e71c: return 0x3a4;
    case 0xe6d6d713: return 0x6fb5;
    case 0xe6d6d710: return 0x6fb2;
    case 0x7ba4d6c2: return 0x4e3;
    case 0xd3fa6683: return 0x4b0;
    case 0xd3fa6685: return 0x4b0;
    case 0xe6d6d711: return 0x6fb3;
    case 0xe6d6d712: return 0x6fb4;
    case 0xe6d6d715: return 0x6faf;
    case 0xe6d6d716: return 0x6fb0;
    case 0xe6d6d717: return 0x6fb1;
    case 0xe6d6d71c: return 0x6fb6;
    case 0xe6d6d71d: return 0x6fb7;
    }
    return 0;
}
}
}
}  // namespace EA::XHTML::Resource

// @ 0x008fd1a0
void HTTPz::SetFilter(LogFilter* p, unsigned mask)
{
    m1d8 = p;
    if (p) {
        unsigned u = p->GetLevelMask();
        if ((u & mask) != 0) {
            m1cc = (int)(u & mask);
            return;
        }
        if ((u & 1) != 0) {
            m1cc = 1;
            return;
        }
        if ((u & 2) != 0) {
            m1cc = 2;
            return;
        }
        m1cc = 0;
        m1d8 = 0;
    }
}

// @ 0x008fd240
AutoRef* AutoRef::operator=(RCObj* p)
{
    RCObj* old = mp;
    if (p != old) {
        RCAddRef(p);
        mp = p;
        RCRelease(old);
    }
    return this;
}

// @ 0x008fd290
D290::D290(int x)
: BaseB2()
{
    m0c = x;
    m10 = 1;
    m14 = 0;
    m18 = 0;
    m1c = 0;
}

// @ 0x008fd350
void __cdecl HandlerMsgCb(unsigned a, unsigned b, int id, HMsg* m)
{
    if (id == 0x700af301) {
        MsgServer* srv = GetServer();
        MsgObj* o = m->f28;
        if (o)
            o->v1();
        o->v2();
        ((int*)o)[4] = m->f4;
        ((AutoRef*)((char*)o + 0x14))->operator=(m->f1c);
        ((AutoRef*)((char*)o + 0x18))->operator=(m->f24);
        srv->Post(0x338cd0e, o, 0, 0);
        o->v2();
    }
}

// @ 0x008fd3d0
HttpHandler::~HttpHandler()
{
    if (inited) {
        client.v()->c5();
        MsgServer* srv = GetServer();
        if (srv) {
            srv->Unregister((IMsgHandler*)this, 0x338cd0e, -9999);
            inited = true;
        }
    }
    if (m1e0)
        operator_delete__(m1e0);
    RelNA(auth);
    if (cache)
        CacheRelease(cache);
    StrFree(lang);
    StrFree(enc);
    StrFree(charset);
    StrFree(accept);
    StrFree(ua);
    HClientDtor(&client);
}

// @ 0x008fd540
HttpHandler::HttpHandler()
: inited(false), ua(kUserAgent, 0x1e)
{
    m1cc = 0;
    mb1d0 = 0;
    mf1d4 = kDefLMRatio;
    cache = 0;
    auth = 0;
    m1e0 = 0;
    m1e4 = 0;
    m1e8 = 0;
    client.v()->c0();
}

// @ 0x008fd670
void HTTPy::SetAcceptEncoding(const char* s)
{
    if (s) {
        mEnc.assign(s, s + strlen(s));
    } else if (mEnc.mpBegin != mEnc.mpEnd) {
        *mEnc.mpBegin = 0;
        mEnc.mpEnd = mEnc.mpBegin;
    }
}

// @ 0x008fd6c0
void HTTPlang::SetAcceptLanguage(const char* s)
{
    if (s) {
        mLang.assign(s, s + strlen(s));
    } else if (mLang.mpBegin != mLang.mpEnd) {
        *mLang.mpBegin = 0;
        mLang.mpEnd = mLang.mpBegin;
    }
}

// @ 0x008fd710
void SetRequestTypeInfo(ResourceRequest* r, const char* s)
{
    char* semi = strstr(s, ";");
    if (semi != 0) {
        r->mType.assign(s, semi);
        char* cs = strstr(s, "charset");
        if (cs != 0) {
            unsigned enc = EncodingFromName(cs + 8);
            if (enc != 0)
                r->SetEncoding(enc, 0);
        }
    } else {
        r->mType.assign(s, s + strlen(s));
    }
}

// @ 0x008fd790
long HttpHandler2::CalculateCacheTimeout(HeaderSet* hdrs)
{
    int idx = 0;
    long maxAge = 0;
    bool found = false;
    const char* hdr;
    if (hdrs->FindHeader(1, &hdr, 0)) {
        do {
            ++idx;
            if (hdr == StrIStr(hdr, "no-cache"))
                return 0;
            if (hdr == StrIStr(hdr, "no-store"))
                return 0;
            if (hdr == StrIStr(hdr, "max-age")) {
                const char* p = strpbrk(hdr, "123456789");
                if (p) {
                    maxAge = strtol(p, 0, 10);
                    if (hdrs->FindHeader(0x19, &hdr, 0))
                        maxAge -= strtol(hdr, 0, 10);
                    found = true;
                }
            }
        } while (hdrs->FindHeader(1, &hdr, idx));
        if (found)
            return maxAge;
    }
    if (hdrs->FindHeader(0x2c, &hdr, 0)) {
        unsigned t1;
        {
            NStrI s1(hdr);
            t1 = ParseHttpDate(&s1);
        }
        if (hdrs->FindHeader(3, &hdr, 0)) {
            unsigned t2;
            {
                NStrD s2(hdr);
                t2 = ParseHttpDate(&s2);
            }
            if (t1 > t2)
                return 0;
            return (long)(t1 - t2);
        }
    }
    if (mbUseLM && hdrs->FindHeader(0x2d, &hdr, 0)) {
        NStrAlloc al;
        unsigned lastMod;
        {
            NStrX s(hdr, al);
            lastMod = ParseHttpDate(&s);
        }
        if (hdrs->FindHeader(3, &hdr, 0)) {
            unsigned date;
            {
                NStrX s(hdr, al);
                date = ParseHttpDate(&s);
            }
            unsigned d = date - lastMod;
            return (long)((float)d * mfLMRatio);
        }
    }
    return 0;
}

// @ 0x008fdaf0
bool HttpHandler2::NotificationTargetTest(const char* name)
{
    if (cache != 0) {
        NStrS s(CtorSprintf(), "%ls", name);
        return cache->Exists(s.b);
    }
    return false;
}

// @ 0x008fdb70
bool HttpHandler2::CheckInit()
{
    if (!inited) {
        jobs.EraseRange(jobs.mpBegin, jobs.mpEnd);
        client.v()->c4();
        client.v()->SetNotificationTarget(HandlerMsgCb, 0);
        client.v()->SetUserAgent(ua.b);
        MsgServer2* srv = GetServer2();
        if (srv) {
            srv->Register(&vt1, 0x338cd0e);
            inited = true;
        } else
            client.v()->c5();
    }
    return inited;
}

// @ 0x008fdc00
bool HttpHandler2::RemoveJobFor(ResourceRequest* r)
{
    JobPair* e = jobs.mpEnd;
    unsigned key = r->mKey;
    JobPair* it = LowerBoundJob(jobs.mpBegin, e, &key, jobs.mbFlag);
    if (it != e && !(key < it->first) && it != it + 1)
        e = it;
    if (e == jobs.mpEnd)
        return false;
    bool ok = client.v()->CancelJob(e->second);
    JobPair* last = jobs.mpEnd;
    if (e + 1 < last) {
        JobPair* src = e + 1;
        JobPair* dst = e;
        do {
            dst->first = src->first;
            dst->second = src->second;
            ++src;
            ++dst;
        } while (src != last);
    }
    jobs.mpEnd = jobs.mpEnd - 1;
    return ok;
}

// @ 0x008fdca0
bool JobMap::erase(const unsigned& key)
{
    JobPair* e = mpEnd;
    JobPair* it = find(key);
    if (it != e) {
        if (it + 1 < e)
            CopyJobs(it + 1, e, it);
        mpEnd = mpEnd - 1;
        return true;
    }
    return false;
}

// @ 0x008fdd10
bool HttpHandler2::ProcessRequest(ResourceRequest* req, bool bForce)
{
    if (!CheckInit())
        return false;
    UnkRef stream;      // released after url is freed, on every return path
    NStrE url;
    url.sprintf("%ls", req->mUrl);
    if (cache == 0) {
        MemStream* ms = new("XHTML/Resource/HTTPHandler/MemoryStream", 0, 0, 0, 0)
            MemStream("XHTML/Resource/HTTPHandler/MemoryStream");
        ms->AddRef();
        ms->SetProperty(1, 1.0f);
        ms->SetProperty(2, 2.0f);
        ms->Open(0, 0);
        if (ms != (MemStream*)stream.p) {
            ms->AddRef();
            IUnk* old = stream.p;
            stream.p = (IUnk*)ms;
            if (old)
                old->Release();
        }
        ms->Release();
    } else {
        if (bForce)
            cache->RemoveCachedData(url.b);
        if (cache->Exists(url.b)) {
            IStreamLike* cached = 0;
            const char* mime = 0;
            if (cache->GetCachedDataStream(url.b, &cached, &mime)) {
                SetRequestTypeInfo(req, mime);
                req->SetStream(cached);
                mpProvider->Complete(req, 2);
                return true;
            }
        }
        if (stream.p) {
            IUnk* old = stream.p;
            stream.p = 0;
            old->Release();
        }
        if (!cache->CreateNewCachedDataStream(&stream.p)) {
            if (req->mpListener)
                req->mpListener->Report(0x2420001, req->mUrl, -1, -1, L"Failed to create cache file.\n");
            mpProvider->Complete(req, 3);
            return false;
        }
    }
    HttpRequestObj* hreq = 0;
    if (CreateHTTPGetRequest(url.b, stream.p, &hreq)) {
        HeaderSet* h = &hreq->hdrs;
        if (accept.b != accept.e)
            h->SetHeader(8, &accept);
        if (charset.b != charset.e)
            h->SetHeader(9, &charset);
        if (enc.b != enc.e)
            h->SetHeader(0xa, &enc);
        if (lang.b != lang.e)
            h->SetHeader(0xb, &lang);
        cJob* job = new("XHTML/Resource/HTTPHandler/cJob", 0, 0, 0, 0) cJob(req->mKey);
        ((IUnk*)job)->AddRef();
        int handle = client.v()->AddNewJob(hreq, job, 0, 0);
        if (handle != 0) {
            unsigned key = req->mKey;
            jobs[key] = handle;
            ((AutoRefAtomic*)&hreq)->~AutoRefAtomic();
            return true;
        }
        ((AutoRefAtomic*)&hreq)->~AutoRefAtomic();
    } else if (hreq) {
        RCAtomic* p = (RCAtomic*)hreq;
        if (_InterlockedDecrement((volatile long*)&p->rc) == 0) {
            _InterlockedExchange((volatile long*)&p->rc, 1);
            ((IUnk*)p)->d0(1);
        }
    }
    return false;
}

// @ 0x008fe0c0
bool IMsgSub::HandleMessage(unsigned id, JobMsg* msg)
{
    HttpHandler2* self = (HttpHandler2*)((char*)this - 0xc);
    if (self->inited && id == 0x338cd0e) {
        if (msg)
            msg->AddRef();
        ResourceRequest* req = self->mpProvider->FindRequest(msg->reqId);
        if (req == 0) {
            msg->Release();
            return true;
        }
        HttpResp* resp = msg->resp;
        unsigned key;
        if (msg->event == 0) {
            const char* hdr;
            if (resp->hdrs.FindHeader(0x2a, &hdr, 0))
                SetRequestTypeInfo(req, hdr);
            IUnk* stream = resp->stream;
            if (self->cache) {
                long timeout = self->CalculateCacheTimeout(&resp->hdrs);
                if (timeout > 0) {
                    self->cache->CommitNewCachedDataStream(stream, resp->size, self->m1cc, 1, hdr, (int)timeout);
                } else {
                    self->cache->CommitNewCachedDataStream(stream, resp->size, 0, 1, 0, -1);
                    req->mb2c = false;
                }
            } else {
                ((MemStream*)stream)->Open(0, 0);
            }
            req->SetStream((IStreamLike*)resp->stream);
            self->mpProvider->Complete(req, 2);
            key = req->mKey;
        } else {
            if (msg->event == 10 && self->auth && !msg->retried && self->auth->Authenticate(resp, msg->job)) {
                if (msg->job->sub1)
                    ((MemStream*)msg->job->sub1)->Open(0, 0);
                if (msg->job->sub2) {
                    ((MemStream*)msg->job->sub2)->Open(0, 0);
                    ((JobSub*)msg->job->sub2)->Reset(0, 0);
                }
                int handle = self->client.v()->AddNewJob(msg->job, msg, 0, 0);
                if (handle != 0) {
                    msg->AddRef();
                    msg->retried = true;
                    key = req->mKey;
                    self->jobs[key] = handle;
                    msg->Release();
                    return true;
                }
            }
            if (self->cache)
                self->cache->CommitNewCachedDataStream(resp->stream, resp->size, 0, 0, 0, -1);
            if (req->mpListener) {
                WStrE ws;
                ws.sprintf(L"Server Message: \"%hs\"", resp->message);
                req->mpListener->Report(resp->code + 0x2420000, req->mUrl, -1, -1, ws.b);
            }
            self->mpProvider->Complete(req, 3);
            key = req->mKey;
        }
        self->jobs.erase(key);
        msg->Release();
    }
    return true;
}
