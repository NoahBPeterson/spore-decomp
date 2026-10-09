// Spore decompilation - batch bfs4, slice s008fc670 (0x008FC670..0x008FD6BF).
// EA::XHTML::Resource handlers (DocumentFactory, FileHandler, HTTPHandler, encoding table).
// Flags: /O2 /MD /Gy /TP /GS-
#include <intrin.h>
#include "types.h"



// ---------------------------------------------------------------------------
// external helpers (relocation-masked)
// ---------------------------------------------------------------------------
extern "C" unsigned __cdecl strlen(const char* s);

// ---------------------------------------------------------------------------
// ref-counted object (vtable slot 0 called with (1) to destroy)
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// HTTPHandler / handler object
// ---------------------------------------------------------------------------
struct HTTPx {
    char pad0[0x1d0];
    uint8_t mb1d0;      // +0x1d0
    char pad1[3];
    float  mf1d4;       // +0x1d4

    void SetFlagBool(bool b, float f);
};

// @ 0x008fd050
void HTTPx::SetFlagBool(bool b, float f)
{
    mb1d0 = b;
    mf1d4 = f;
}

// @ 0x008fd080
const wchar_t* __stdcall GetProtocolName(int i)
{
    if (i == 0)
        return L"http";
    return i == 1 ? L"https" : 0;
}

// ---------------------------------------------------------------------------
// EncodingFromName: FNV-1a hash of the (narrow) name mapped to a code page
// ---------------------------------------------------------------------------
unsigned __cdecl FnvHash(const char* s, unsigned h, int a);

// @ 0x008fd0a0
unsigned EncodingFromName(const char* name)
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

// ---------------------------------------------------------------------------
// small EASTL string used for the Accept-* headers
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// multiple-inheritance handler objects (ctor stores two vtables)
// ---------------------------------------------------------------------------
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

// @ 0x008fd290
D290::D290(int x) : BaseB2()
{
    m0c = x;
    m10 = 1;
    m14 = 0;
    m18 = 0;
    m1c = 0;
}

struct AutoRefD {
    RCObj* mp;
    ~AutoRefD() { RCRelease(mp); }
};

struct D2e0 : BaseA2, BaseB2 {
    char pad[0x14 - 0xc];
    AutoRefD m14;   // +0x14
    AutoRefD m18;   // +0x18
    ~D2e0();
};

// @ 0x008fd2e0
D2e0::~D2e0() {}

// ---------------------------------------------------------------------------
// LogFilter setter
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// large handler entry points (approximate: bodies summarize the observed calls)
// ---------------------------------------------------------------------------
// ---------------------------------------------------------------------------
// HTTPHandler (retail layout; two vtables at +0 and +0xc, HTTPClient embedded at +0x10)
// ---------------------------------------------------------------------------
extern "C" void* __cdecl memcpy(void*, const void*, unsigned);
#pragma function(memcpy)
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
extern char kVtHandlerBase0[];
extern char kVtHandlerBase1[];
extern char kVtHandler0[];
extern char kVtHandler1[];
extern const char kUserAgent[31];   // 0x01439e20
extern const float kDefLMRatio;     // 0x013ec480

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
HttpHandler::HttpHandler() : inited(false), ua(kUserAgent, 0x1e)
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

// ---------------------------------------------------------------------------
// TextStyle::Update (0x008fc670): resolve font sizes against the parent style, query the
// font server for metrics and merge the per-style string tables into the parent
// ---------------------------------------------------------------------------
extern "C" double __cdecl floor(double);

struct Box5 {
    union {
        float v[5];
        uint32_t u[5];
    };
};

struct UnitA { int v; float Resolve(float base, const Box5* box); };   // 0x8f9660
struct UnitB { int v; float Resolve(float base, const Box5* box); };   // 0x8f95c0

struct FontMetrics {
    int f0;
    int f4;
    int f8;
    int fc;
    float f10;      // +0x10
    float f14;      // +0x14
    int f18, f1c, f20;
    float f24;      // +0x24
    int pad[4];
};
struct FontObj {
    virtual void o0(); virtual void o1(); virtual void o2();
    virtual void Release();                                   // +0xc
    virtual void o4(); virtual void o5(); virtual void o6(); virtual void o7(); virtual void o8();
    virtual void o9(); virtual void o10(); virtual void o11();
    virtual bool GetMetrics(FontMetrics* m);                  // +0x30
};
struct FontServer {
    virtual void f0(); virtual void f1(); virtual void f2(); virtual void f3(); virtual void f4();
    virtual void f5(); virtual void f6();
    virtual FontObj* GetFont(void* spec, int a, int b, int c, int d, int e);   // +0x1c
};
FontServer* __cdecl GetFontServer(int);

struct HNodeA { const void* key; const void* val; HNodeA* next; };
struct HItA { HNodeA* node; HNodeA** bucket; HItA() {} HItA(const HItA& o) : node(o.node), bucket(o.bucket) {} };
struct HMapA {
    int al;
    HNodeA** mpBucketArray;
    unsigned mnBucketCount;
    char pad[0x20 - 12];
    HItA begin();                                   // 0x594410
    const void*& operator[](const void* const& key);    // 0x8fc610
};
struct HNodeB { const void* key; int val; HNodeB* next; };
struct HItB {
    HNodeB* node; HNodeB** bucket;
    HItB() {}
    HItB(const HItB& o) : node(o.node), bucket(o.bucket) {}
    void increment()
    {
        node = node->next;
        while (node == 0)
            node = *++bucket;
    }
};
struct HMapB {
    int al;
    HNodeB** mpBucketArray;
    unsigned mnBucketCount;
    char pad[0x20 - 12];
    HItB find(const void* const& key);              // 0x8fbbf0
    HItB insert(const HNodeB& v, bool tag);         // 0x8fbc80
    HItB begin()
    {
        HItB it;
        it.bucket = mpBucketArray;
        it.node = *it.bucket;
        if (it.node == 0) {
            do {
                ++it.bucket;
            } while (*it.bucket == 0);
            it.node = *it.bucket;
        }
        return it;
    }
    HNodeB* end() { return mpBucketArray[mnBucketCount]; }
    int& operator[](const void* const& key)
    {
        HItB it = find(key);
        if (it.node == end()) {
            HNodeB v;
            v.key = key;
            v.val = 0;
            it = insert(v, false);
        }
        return it.node->val;
    }
};

template <typename T> inline const T& Clamp(const T& v, const T& lo, const T& hi)
{
    return (v > hi) ? hi : ((lo > v) ? lo : v);
}
unsigned __cdecl BlendColor(unsigned c, unsigned d);            // 0x8fb7e0

struct TextStyle {
    TextStyle* parent;          // +0
    int pad4;
    uint8_t dirty;              // +8
    char pad9[3];
    char font[0x20c - 0xc];     // +0xc (font spec)
    float size;                 // +0x20c
    char pad210[0x220 - 0x210];
    int flag220;                // +0x220
    char pad224[0x230 - 0x224];
    int m230;                   // +0x230
    char pad234[0x278 - 0x234];
    float f278, f27c, f280;
    UnitA u284;                 // +0x284
    int m288;
    int m28c;
    UnitA u290;
    int pad294;
    UnitA u298;
    int m29c;
    char pad2a0[0x2bc - 0x2a0];
    unsigned color;             // +0x2bc
    unsigned color2;            // +0x2c0
    UnitB u2c4;
    int pad2c8;
    UnitB u2cc;
    char pad2d0[0x3a8 - 0x2d0];
    int m3a8;
    char pad3ac[0x3bc - 0x3ac];
    HMapA tbl3bc;               // +0x3bc
    HMapB tbl3dc;               // +0x3dc
    HMapA tbl3fc;               // +0x3fc
    char pad41c[0x430 - 0x41c];
    Box5 box;                   // +0x430
    void Update();
};

// @ 0x008fc670
void TextStyle::Update()
{
    if (m3a8 == 0)
        return;
    if (dirty) {
        m230 = m28c;
        Box5 base;
        if (parent) {
            base.u[0] = parent->box.u[0];
            base.u[1] = parent->box.u[1];
            base.u[2] = parent->box.u[2];
            base.u[3] = parent->box.u[3];
            base.u[4] = parent->box.u[4];
        } else {
            base.v[0] = 10.0f;
            base.v[1] = 10.0f;
            base.v[2] = 10.0f;
            base.v[3] = 10.0f;
            base.v[4] = 0.0f;
        }
        float sz;
        if (m288 == 10)
            sz = base.v[0];
        else
            sz = (float)floor((double)u284.Resolve(base.v[0], &base) + 0.5f);
        float lineSz;
        if (m29c == 10)
            lineSz = 12.0f;
        else
            lineSz = u298.Resolve(base.v[0], &base);
        const float& r = Clamp(sz, 6.0f, 256.0f);
        size = r;
        flag220 = lineSz < r;
        box.v[0] = r;
        box.v[2] = r;
        box.v[1] = r;
        box.v[3] = r;
        box.v[4] = 0.0f;
        FontServer* srv = GetFontServer(0);
        if (srv) {
            FontObj* fo = srv->GetFont(font, 0, 0, 0xffff, -1, 1);
            if (fo) {
                FontMetrics m;
                m.f4 = 0;
                if (fo->GetMetrics(&m)) {
                    box.v[2] = m.f24;
                    box.v[1] = m.f24;
                    box.v[3] = m.f10;
                    box.v[4] = m.f14;
                }
                fo->Release();
            }
        }
        f278 = (float)floor((double)u2cc.Resolve(base.v[0], &base));
        f27c = (float)floor((double)u2c4.Resolve(base.v[0], &base));
        f280 = (float)floor((double)u290.Resolve(base.v[0], &base));
        dirty = 0;
    }
    unsigned c = color;
    if ((c >> 24) != 0xff)
        c = BlendColor(c, color2);
    color2 = c;
    if (parent) {
        HItA it = tbl3fc.begin();
        HNodeA* node = it.node;
        HNodeA** bucket = it.bucket;
        if (node != tbl3fc.mpBucketArray[tbl3fc.mnBucketCount]) {
            do {
                const void* val = node->val;
                parent->tbl3bc[node->key] = val;
                node = node->next;
                while (node == 0)
                    node = *++bucket;
            } while (node != tbl3fc.mpBucketArray[tbl3fc.mnBucketCount]);
        }
        HItB it2 = tbl3dc.begin();
        while (it2.node != tbl3dc.end()) {
            HMapB* m = (HMapB*)&parent->tbl3bc;
            (*m)[it2.node->key] += it2.node->val;
            it2.increment();
        }
    }
}

// ---------------------------------------------------------------------------
// DocumentFactory::CreateResource
// ---------------------------------------------------------------------------
extern "C" int __cdecl strcmp(const char*, const char*);
#pragma intrinsic(strcmp)
void* __cdecl operator_new(unsigned size, const char* name, int a, int b, int c, int d);   // 0x00f473a0
extern const char* gMimeTextHtml;       // "text/html"

struct DomDoc {
    virtual void AddRef();
    virtual void Release();
    char pad[0x44 - 4];
    int mSourceId;      // +0x44
    char pad2[0x31c - 0x48];
    DomDoc(int arg);                    // 0x008e2dd0
};
inline void* operator new(unsigned size, const char* name, int a, int b, int c, int d)
{
    return operator_new(size, name, a, b, c, d);
}
struct DocPtr {
    DomDoc* mp;
    DocPtr(DomDoc* p) : mp(p) { if (mp) mp->AddRef(); }
    ~DocPtr() { if (mp) mp->Release(); }
    operator DomDoc*() const { return mp; }
    DomDoc* operator->() const { return mp; }
};
struct DomStream {
    virtual void d0(); virtual void d1(); virtual void d2(); virtual void d3();
    virtual void d4(); virtual void d5(); virtual void d6();
    virtual int Size();                 // +0x1c
};
struct XmlParser {
    char raw[0x43c];
    XmlParser(DomDoc* doc);                // 0x008e5ea0
    ~XmlParser();                          // 0x008e5ca0
    int Parse(DomStream* s);               // 0x008e60a0
};

struct DocRequest {
    char pad0[8];
    int mId;            // +8
    int mArg;           // +0xc
    const char* mMime;  // +0x10
    char pad1[0x3c - 0x14];
    DomStream* mStream; // +0x3c
};

// @ 0x008fcab0
int __stdcall DocumentFactory_CreateResource(DomDoc** outDoc, int* outSize, DocRequest* req)
{
    if (strcmp(req->mMime, gMimeTextHtml) == 0) {
        DomDoc* raw = new("XHTML/DocumentFactory/Document", 0, 0, 0, 0) DomDoc(req->mArg);
        DocPtr doc(raw);
        DomStream* stream = req->mStream;
        *outSize = stream->Size();
        XmlParser parser(doc);
        doc->mSourceId = req->mId;
        if (parser.Parse(stream))
            return 1;
        doc->AddRef();
        *outDoc = doc;
        return 0;
    }
    return 3;
}

// ---------------------------------------------------------------------------
// Leading "./", "../" and "/" removal on a wide path string (EASTL basic_string<wchar_t>)
// ---------------------------------------------------------------------------
typedef unsigned int size_type;
typedef int ptrdiff_t_;
extern "C" void* __cdecl memmove(void*, const void*, unsigned);
template <typename T> inline const T& min_alt(const T& a, const T& b) { return b < a ? b : a; }
inline size_type CharStrlen(const wchar_t* s)
{
    const wchar_t* p = s;
    while (*p)
        ++p;
    return (size_type)(p - s);
}
inline int CharCompare(const wchar_t* p1, const wchar_t* p2, size_type n)
{
    for (; n > 0; ++p1, ++p2, --n) {
        if (*p1 != *p2)
            return (*p1 < *p2) ? -1 : 1;
    }
    return 0;
}
inline int StrCompare(const wchar_t* pBegin1, const wchar_t* pEnd1, const wchar_t* pBegin2, const wchar_t* pEnd2)
{
    const ptrdiff_t_ n1 = pEnd1 - pBegin1;
    const ptrdiff_t_ n2 = pEnd2 - pBegin2;
    const ptrdiff_t_ nMin = min_alt(n1, n2);
    const int cmp = CharCompare(pBegin1, pBegin2, (size_type)nMin);
    return (cmp != 0 ? cmp : (n1 < n2 ? -1 : (n1 > n2 ? 1 : 0)));
}
struct WStr {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    size_type size() const { return (size_type)(mpEnd - mpBegin); }
    int compare(size_type pos1, size_type n1, const wchar_t* p) const
    {
        return StrCompare(mpBegin + pos1, mpBegin + pos1 + min_alt(n1, size() - pos1), p, p + CharStrlen(p));
    }
    void erase(wchar_t* first, wchar_t* last)
    {
        if (first != last) {
            memmove(first, last, (size_type)((mpEnd - last) + 1) * sizeof(wchar_t));
            mpEnd -= (last - first);
        }
    }
};
wchar_t* __cdecl PathComponentEnd(wchar_t* first, wchar_t* last, int n);    // 0x920da0

// @ 0x008fcbd0
void __cdecl StripLeadingDotComponents(WStr* s)
{
    wchar_t* pos = PathComponentEnd(s->mpBegin, s->mpEnd, 0);
    while (pos != s->mpEnd) {
        const size_type idx = (size_type)(pos - s->mpBegin);
        if (s->compare(0, idx, L".") != 0 && s->compare(0, idx, L"..") != 0 && s->compare(0, idx, L"") != 0)
            return;
        s->erase(s->mpBegin, pos + 1);
        pos = PathComponentEnd(s->mpBegin, s->mpEnd, 0);
    }
}

// ---------------------------------------------------------------------------
// FileHandler::ProcessRequest
// ---------------------------------------------------------------------------
struct FStr96 {
    wchar_t* mpBegin;
    wchar_t* mpEnd;
    wchar_t* mpCapacity;
    const char* mpName;
    wchar_t* mpPoolBegin;
    wchar_t mBuf[96];
    FStr96()
    {
        mpPoolBegin = mBuf;
        mpBegin = mBuf;
        mpCapacity = mBuf + 96;
        mpEnd = mBuf;
        mBuf[0] = 0;
    }
    FStr96(const FStr96& x);                // 0x5d7270
    void DeallocateSelf()
    {
        if ((int)((mpCapacity - mpBegin) * 2) > 2 && mpBegin && mpBegin != mpPoolBegin)
            operator_delete__(mpBegin);
    }
    ~FStr96() { DeallocateSelf(); }
};

struct FSStream {
    virtual void d0();
    virtual void AddRef();                  // +4
    virtual void Release();                 // +8
    virtual void d3(); virtual void d4(); virtual void d5(); virtual void d6(); virtual void d7();
    virtual void d8(); virtual void d9(); virtual void d10(); virtual void d11(); virtual void d12();
    virtual void d13(); virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17(); virtual void d18();
    virtual bool Open(int access, int disp, int share, int flags);  // +0x4c
    char pad[0x22c - 4];
    FSStream(const wchar_t* path);          // 0x931e10
};

struct FileReq {
    char pad0[0xc];
    const char* mUrl;       // +0xc
    void SetContentType(const wchar_t* t);  // 0xa355e0
    void SetStream(FSStream* s);            // 0x836480
};
struct ReqProvider {
    void Complete(FileReq* r, int status);  // 0x8ffb40
};
struct HIt {
    void* node;
    void* bucket;
    HIt() {}
    HIt(const HIt& o) : node(o.node), bucket(o.bucket) {}
};
struct ExtMap {
    int mAlloc;
    void** mpBucketArray;   // +4
    unsigned mnBucketCount; // +8
    HIt find(const wchar_t* const& key);    // 0x8fbbf0
};
struct ExtNode { void* next; const wchar_t* second; };
bool __cdecl ConvertURLToFilePath(const char* url, FStr96* out);
void __cdecl PathSimplify(FStr96* s);       // 0x921140
FStr96* __cdecl PathJoin(FStr96* a, const FStr96* b);   // 0x921210
const wchar_t* __cdecl PathGetFileName(const FStr96* s);// 0x920ee0

struct FileHandler {
    void* vt;
    int rc;
    ReqProvider* mpProvider;    // +8
    ExtMap mExt;                // +0xc
    char pad[0x2c - 0x18];
    FStr96 mBase;               // +0x2c
    bool ProcessRequest(FileReq* req, int unused);
};

// @ 0x008fce50
bool FileHandler::ProcessRequest(FileReq* req, int unused)
{
    if (mpProvider == 0)
        return false;
    FStr96 path;
    if (ConvertURLToFilePath(req->mUrl, &path)) {
        PathSimplify(&path);
        StripLeadingDotComponents((WStr*)&path);
        if (path.mpBegin != path.mpEnd) {
            FStr96 full(mBase);
            PathJoin(&full, &path);
            const wchar_t* ext = PathGetFileName(&full);
            if (*ext == L'.')
                ++ext;
            HIt it = mExt.find(ext);
            if (it.node != mExt.mpBucketArray[mExt.mnBucketCount])
                req->SetContentType(((ExtNode*)it.node)->second);
            FSStream* fs = new("FileHandler/FileStream", 0, 0, 0, 0) FSStream(full.mpBegin);
            if (fs) {
                fs->AddRef();
                if (fs->Open(1, 6, 1, 0)) {
                    req->SetStream(fs);
                    mpProvider->Complete(req, 2);
                    fs->Release();
                    return true;
                }
                fs->Release();
            }
        }
    }
    mpProvider->Complete(req, 3);
    return false;
}
// --- equivalence checker address annotations
    void operator_new(...); // 0x00f473a0

// --- equivalence checker address annotations (dummy declarations) ---
namespace __equiv_ann {
struct EStr16 {
    void RangeInit(unsigned int); // 0x00475ab0
};
struct XmlParser {
    ~XmlParser(); // 0x008e5ca0
    void Parse(void*); // 0x008e60a0
    XmlParser(void*); // 0x008e5ea0
};
struct HClient {
    HClient(); // 0x00943f60
};
struct DomDoc {
    DomDoc(int); // 0x008e2dd0
};
}
