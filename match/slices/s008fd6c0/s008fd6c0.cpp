// Spore decompilation - batch bfs4, slice s008fd6c0 (0x008FD6C0..0x008FE60F).
// EA::XHTML::Resource HTTP handler requests + intrusive_hashtable (wide-string hashing).
// Flags: /O2 /MD /Gy /TP /GS- /arch:SSE2
#include <intrin.h>
#include "types.h"

typedef unsigned short wchar16;

void __cdecl operator_delete__(void* p);
extern "C" unsigned __cdecl strlen(const char* s);
extern "C" __declspec(dllimport) char* __cdecl strstr(const char* s, const char* sub);
extern "C" int __cdecl wcscmp(const wchar_t* a, const wchar_t* b);
unsigned __cdecl EncodingFromName(const char* name);

// ---------------------------------------------------------------------------
// EASTL narrow string
// ---------------------------------------------------------------------------
struct EStr {
    char* mpBegin;
    char* mpEnd;
    void assign(const char* first, const char* last);
};

// @ 0x008fd6c0
struct HTTPlang {
    char pad0[0x1bc];
    EStr mLang;             // +0x1bc
    void SetAcceptLanguage(const char* s);
};

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
    void SetEncoding(unsigned enc, int a);
    void SetStream(IStreamLike* s);     // 0x836480
};

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

// @ 0x008fe380
struct Ratio {
    char pad0[0x144];
    unsigned m144;          // +0x144
    unsigned m148;          // +0x148
    uint16_t m14c;          // +0x14c
    void Set(int v, uint16_t den);
};

void Ratio::Set(int v, uint16_t den)
{
    m148 = (unsigned)v;
    m148 = m14c ? m144 / m14c : 0;
    m14c = den;
    m148 = den ? m144 / den : 0;
}

// @ 0x008fe3f0
const wchar16* FindFirstOf(const wchar16* first, const wchar16* last,
                           const wchar16* sfirst, const wchar16* slast)
{
    for (; first != last; ++first)
        for (const wchar16* s = sfirst; s != slast; ++s)
            if (*first == *s)
                return first;
    return last;
}

// @ 0x008fe430
// eastl::intrusive_hashtable<...>::DoFindNode: a thiscall member that never uses this.
struct IHTableWIter {
    int* mpNode;
    int** mpBucket;
    IHTableWIter(int* n, int** b) : mpNode(n), mpBucket(b) {}
};
struct IHTableW {
    int* mBucket[64];
    int* mEnd;                      // +0x100 end sentinel
    int* DoFindNode(int* node, const wchar16** key) const;
    IHTableWIter find(const wchar16** key);
};
int* IHTableW::DoFindNode(int* node, const wchar16** key) const
{
    while (node) {
        const wchar16* a = *key;
        const wchar16* b = *(const wchar16**)((char*)node + 4);
        while (*a && *a == *b) {
            ++a;
            ++b;
        }
        if (*a == *b)
            return node;
        node = (int*)*node;
    }
    return 0;
}

// @ 0x008fe490
// intrusive_hashtable::find: inlined FNV-1 hash, returns an 8-byte iterator via sret.
IHTableWIter IHTableW::find(const wchar16** key)
{
    const wchar16* s = *key;
    unsigned h = 0x811c9dc5;
    unsigned c = *s;
    while (c != 0) {
        ++s;
        h = (h * 0x1000193) ^ c;
        c = *s;
    }
    int** bucket = &mBucket[h & 0x3f];
    int* node = DoFindNode(*bucket, key);
    return node ? IHTableWIter(node, bucket) : IHTableWIter(mEnd, &mEnd);
}

// @ 0x008fe510
struct IHNode {
    IHNode* mpNext;
    const wchar_t* mKey;
};
inline bool StrEq16(const wchar_t* a, const wchar_t* b)
{
    while (*a && *a == *b) {
        ++a;
        ++b;
    }
    return *a == *b;
}
struct IHTable {
    IHNode* mBucket[64];
    unsigned mn100;
    unsigned mnElementCount;        // +0x104
    unsigned erase(const wchar_t* const& k);
};

unsigned IHTable::erase(const wchar_t* const& k)
{
    const wchar_t* s = k;
    unsigned h = 0x811c9dc5;
    unsigned c = *s;
    while (c != 0) {
        ++s;
        h = (h * 0x1000193) ^ c;
        c = *s;
    }
    const unsigned nBefore = mnElementCount;
    IHNode** ppBucket = &mBucket[h & 0x3f];
    while (*ppBucket && StrEq16(k, (*ppBucket)->mKey)) {
        *ppBucket = (*ppBucket)->mpNext;
        --mnElementCount;
    }
    IHNode* pNode = *ppBucket;
    if (pNode) {
        IHNode* pNext;
        while ((pNext = pNode->mpNext) != 0) {
            if (StrEq16(k, pNext->mKey)) {
                pNode->mpNext = pNext->mpNext;
                --mnElementCount;
            } else {
                pNode = pNode->mpNext;
            }
        }
    }
    return nBefore - mnElementCount;
}

// ---------------------------------------------------------------------------
// HTTPHandler (retail layout). Two bases: IProtocolHandler (+0) and IMsgHandler (+0xc);
// the HTTPClient is embedded at +0x10.
// ---------------------------------------------------------------------------
extern "C" void* __cdecl memcpy(void*, const void*, unsigned);
#pragma function(memcpy)
#pragma intrinsic(strlen)
extern "C" __declspec(dllimport) char* __cdecl strpbrk(const char*, const char*);
extern "C" __declspec(dllimport) long __cdecl strtol(const char*, char**, int);
void* __cdecl operator_new(unsigned size, const char* name, int a, int b, const char* file, int line);
void* __cdecl operator_new(unsigned size, const char* name, int a, int b, int c, int d);
inline void* operator new(unsigned size, const char* name, int a, int b, int c, int d)
{
    return operator_new(size, name, a, b, c, d);
}
extern char gEmptyStr[2];
extern wchar_t gEmptyWStr[2];
const char* __cdecl StrIStr(const char* hay, const char* needle);      // 0x92cc00

struct IUnk {
    virtual void d0(int);
    virtual void AddRef();          // +4
    virtual void Release();         // +8
};

struct HeaderSet {
    bool FindHeader(int field, const char** out, int index);                // 0x9420e0
    void SetHeader(int field, const void* str);                            // 0x944d50
};

// -- narrow string flavours that differ only in which members the compiler left out of line --
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
struct JobCtl {
    virtual void j0(); virtual void j1(); virtual void j2(); virtual void j3(); virtual void j4();
    virtual void j5(); virtual void j6(); virtual void j7();
    virtual void j8();
    virtual void Reset(int a, int b);                   // +0x28 is index 10; see below
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
    int pad8;
    int reqId;                  // +0xc
    int event;                  // +0x10
    JobHolder* job;             // +0x14
    HttpResp* resp;             // +0x18
    bool retried;               // +0x1c
};

// the HTTPClient embedded in HTTPHandler: vtable + opaque data
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
struct DomRequestHandle;
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
struct RCUnk2 { virtual void d0(int); virtual void AddRef(); virtual void Release(); };
struct IMsgHandler2 {
    virtual void m0();
    virtual bool HandleMessage(unsigned id, void* msg);
};
struct AuthSvc {
    virtual void a0();
    virtual bool Authenticate(HttpResp* resp, void* job);           // +4
};

struct cJob {
    cJob(unsigned key);                             // 0x8fd290
};
struct MemStream {
    virtual void d0(int);
    virtual void AddRef();                          // +4
    virtual void Release();                         // +8
    virtual void v3(); virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
    virtual void v8(); virtual void v9();
    virtual void Open(int a, int b);                // +0x28
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
    NStrE url;
    IUnk* stream = 0;
    url.sprintf("%ls", req->mUrl);
    if (cache == 0) {
        MemStream* ms = new("XHTML/Resource/HTTPHandler/MemoryStream", 0, 0, 0, 0)
            MemStream("XHTML/Resource/HTTPHandler/MemoryStream");
        ms->AddRef();
        ms->SetProperty(1, 1.0f);
        ms->SetProperty(2, 2.0f);
        ms->Open(0, 0);
        if (ms != (MemStream*)stream) {
            ms->AddRef();
            IUnk* old = stream;
            stream = (IUnk*)ms;
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
                if (stream)
                    stream->Release();
                return true;
            }
        }
        if (stream) {
            IUnk* old = stream;
            stream = 0;
            old->Release();
        }
        if (!cache->CreateNewCachedDataStream(&stream)) {
            if (req->mpListener)
                req->mpListener->Report(0x2420001, req->mUrl, -1, -1, L"Failed to create cache file.\n");
            mpProvider->Complete(req, 3);
            return false;
        }
    }
    HttpRequestObj* hreq = 0;
    if (CreateHTTPGetRequest(url.b, stream, &hreq)) {
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
