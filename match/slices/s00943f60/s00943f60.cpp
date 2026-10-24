// Slice s00943f60 -- EA::Internet::HTTPClient::Shutdown (0x009440e0).
// Module flags: /O2 /MD /Gy /EHsc /TP /GS-
#include "types.h"
#include <intrin.h>
#include <new>

void __cdecl operator_delete__(void*) throw();   // 0x00f47380

typedef void (__thiscall *VF0)(void*);
typedef int  (__thiscall *VFI0)(void*);
#define VSLOT(p, byteoff) ((*(void***)(p))[(byteoff) / 4])
#define VCALL0(p, off)    ((VF0)VSLOT(p, off))(p)
#define VCALLI0(p, off)   ((VFI0)VSLOT(p, off))(p)

namespace EA { namespace Thread {
class Mutex { public:
    void Lock(const void* timeout);   // 0x009221b0
    void Unlock();                    // 0x00922270
};
}}

namespace EA { namespace Internet {

extern const int kLockTimeout;        // 0x0143F214

typedef void (__cdecl *NotifyFn)(void* ctx, void* client, unsigned msg, void* data, int zero);

// Refcounted filter object: vtable slot 0 is the deleting destructor, count at +4.
struct RefObj {
    virtual void Destroy(int flags);
    int mnRefCount;
};

// Worker thread info (0x90 of the client): bCreated at +4, socket at +0x20.
struct WorkerThreadInfo {
    int   pad0;
    char  bCreated;                   // +4
    char  pad1[0x20 - 5];
    void* mpSocket;                   // +0x20
};

class HTTPClient {
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
    EA::Thread::Mutex mMutex;         // +0x60
    char pad4[0x90 - 0x61];
    WorkerThreadInfo* mpWorkerThreadInfo;   // +0x90
    char pad5[0x140 - 0x94];
    char* mpReadBuffer;               // +0x140
    char pad7[0x148 - 0x144];
    char* mpWriteBuffer;              // +0x148 (freed when non-null)
    char pad6[0x150 - 0x14c];
    RefObj** mpFiltersBegin;          // +0x150
    RefObj** mpFiltersEnd;            // +0x154

    void SetTimeout(int a, int ms);   // 0x00943a30
    void Pump(void* socket);          // 0x009421b0
    bool Shutdown();
};

// @ 0x009440e0  EA::Internet::HTTPClient::Shutdown  (ecx = this)
bool HTTPClient::Shutdown() {
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
        WorkerThreadInfo* info = mpWorkerThreadInfo;
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
        RefObj* p = *--mpFiltersEnd;
        int old = _InterlockedExchangeAdd((volatile long*)&p->mnRefCount, -1);
        if (old - 1 == 0) {
            _InterlockedExchange((volatile long*)&p->mnRefCount, 1);
            if (p)
                p->Destroy(1);
        }
    }
    return true;
}

// ===========================================================================
// Part 2 -- the EA::Internet HTTP request/response slice (0x00943f60..0x00944e10).
//
//  00943f60  EA::Internet::HTTPClient::HTTPClient
//  00944250  eastl::basic_string<char>::push_back(char)
//  009442e0  UTFInternet::HTTPRequest::HTTPRequest
//  00944380  UTFInternet::HTTPRequest::~HTTPRequest
//  00944450  CreateHTTPGetRequest
//  00944570  UTFInternet::HTTPClient::~HTTPClient
//  00944660  UTFInternet::HTTPRequest::AddRequestParameter
//  00944850  eastl::vector<pair<string,string>>::erase
//  009448c0  eastl::vector<pair<string,string>>::insert (grow path)
//  00944a10  UTFInternet::HTTPRequest::AddRequestParameterStr (tail-jump thunk)
//  00944a30  EA::Internet::HTTPHeaders::RemoveHeaderEntryWorker
//  00944ac0  EA::Internet::HTTPHeaders::RemoveHeaderEntry
//  00944af0  eastl::vector<pair<string,string>>::push_back (empty header pair)
//  00944bd0  EA::Internet::HTTPResponse::Clear
//  00944cb0  EA::Internet::HTTPHeaders::AddHeaderEntry
//  00944d00  EA::Internet::HTTPHeaders::AddHeaderEntryV (nullable value)
//  00944d50  EA::Internet::HTTPHeaders::AddHeaderEntryField (by field id)
//  00944db0  EA::Internet::HTTPHeaders::AddHeaderEntryFieldV (by field id, nullable)
//  00944e10  EA::Internet::HTTPClient::AddCookie
// ===========================================================================

typedef unsigned int   u32;
typedef unsigned short u16;
typedef unsigned char  u8;

// Grow helper (0x0061c280) reached from both the heap and SSO string push_back paths.
extern "C" void __cdecl sso_grow(void* s, u32 n);

// ------------------------------------------------------------------ eastl

namespace eastl {

// Heap string: 3 pointers + a 4-byte allocator pad.
template <class T>
struct basic_string {
    T*  mpBegin;                 // +0x00
    T*  mpEnd;                   // +0x04
    T*  mpCapacity;              // +0x08
    int mAllocator;              // +0x0c

    void clear() { if (mpBegin != mpEnd) { *mpBegin = 0; mpEnd = mpBegin; } }
    void push_back(char c);                            // 0x00944250
    void Destroy() {
        if ((int)(mpCapacity - mpBegin) > 1 && mpBegin != 0)
            operator_delete__(mpBegin);
    }
    void Erase(u32 pos, u32 n);                        // 0x0061e200
};

// SSO string: 0x14 header (3 pointers + pad + self-pointer) then an inline buffer.
template <int N>
struct sso_string {
    char* mpBegin;                 // +0x00
    char* mpEnd;                   // +0x04
    char* mpCapacity;              // +0x08
    int   mPad0c;                  // +0x0c
    char* mpSelf;                  // +0x10
    char  mBuffer[N];              // +0x14

    void init() {
        mpSelf = mBuffer;
        mpEnd = mBuffer;
        mpBegin = mBuffer;
        mpCapacity = mBuffer + N;
        *mBuffer = 0;
    }
    void Destroy() {
        char* b = mpBegin;
        if ((int)(mpCapacity - b) > 1 && b != 0 && b != mpSelf)
            operator_delete__(b);
    }
    void append(const char* first, const char* last);  // 0x0060a150
    void assign(const char* first, const char* last);  // 0x0060a2c0
    void push_back(char c) {
        if (mpEnd + 1 == mpCapacity) {
            u32 size   = (u32)(mpCapacity - mpBegin);
            u32 newLen = (u32)(mpEnd - mpBegin) + 1;
            u32 cap    = size - 1;
            if (cap < 9)
                cap = 8;
            else
                cap = cap * 2;
            u32 want = (newLen <= cap) ? cap : newLen;
            u32 cur  = (u32)(mpEnd - mpBegin);
            u32 low  = (cur <= want) ? cur : want;
            if (size < low + 1)
                sso_grow(this, low + 1);
        }
        *mpEnd = c;
        ++mpEnd;
        *mpEnd = 0;
    }
    void DeallocateSelf();                             // 0x00919a40
};

// The 0x54-byte header string used by the HTTP header array (pair element halves).
struct StrStub {
    char* mpBegin;                 // +0x00
    char* mpEnd;                   // +0x04
    char* mpCapacity;              // +0x08
    int   mPad0c;                  // +0x0c
    char* mpSelf;                  // +0x10
    char  mBuffer[0x40];           // +0x14 (total 0x54)

    void init() {
        mpSelf = mBuffer;
        mpEnd = mBuffer;
        mpBegin = mBuffer;
        mpCapacity = mBuffer + 0x40;
        *mBuffer = 0;
    }
    void Destroy() {
        char* b = mpBegin;
        if ((int)(mpCapacity - b) > 1 && b != 0 && b != mpSelf)
            operator_delete__(b);
    }
    StrStub* assign(const char* s);   // 0x00943570
};

}  // namespace eastl

typedef eastl::basic_string<char>         HeapString;
typedef eastl::sso_string<0x200>          SsoString200;
typedef eastl::sso_string<0x10>           SsoString10;
typedef eastl::StrStub                    HeaderString;

// ------------------------------------------------------------------ helpers

extern "C" void* __cdecl eastl_allocate(u32 size, const char* name, int a, int b,
                                        const char* file, int line);   // 0x00f473a0
void* __cdecl operator_new(u32 size, const char* name, int a, int b,
                           const char* file, int line);                // 0x00f473a0
extern "C" void  __cdecl FUN_0047c600(u32 n);                          // 0x0047c600
extern "C" const char* __cdecl HeaderFieldToFieldString(int field);    // 0x00941c40
extern "C" __declspec(dllimport) int __cdecl _stricmp(const char*, const char*);
extern "C" __declspec(dllimport) size_t __cdecl strlen(const char*);

static const char kEastlFile[] =
    "c:\\BuildAgent\\max-spore001-spore\\CMBuild\\SporeEP1_RL\\Core\\UTFKernel\\EASTL\\include\\EASTL/allocator.h";
static const char kEastlName[] = "EASTL";

// The empty-string sentinels (eastl::gEmptyString for 8/16 bit).
static char* const kVtblEmpty8  = (char*)0x01667bac;
static char* const kVtblEmpty8b = (char*)0x01667bad;
static char* const kVtblEmpty16 = (char*)0x01667bae;

// ------------------------------------------------------------------ URL

// The large EA::Internet URL string policy object (0x2c4 bytes) used by the request.
struct URLClass {
    char mPad[0xb0];                                   // +0x000 .. +0x0af  (total 0xb0)

    void Construct();                                  // 0x0094a4c0
    void SetURL(const char* psz, bool strict);         // 0x0094a6a0
    void Destroy();                                    // 0x0060a100
    HeapString* GetString();                           // 0x0097e850 (returns the URL text)
};

// ConvertPathToEncodedForm(const char* path, sso, bool) -> bool
extern "C" bool __cdecl URL_ConvertPathToEncodedForm(const char* path, void* out, int mode); // 0x0094b610

// ------------------------------------------------------------------ HTTP records

// The HTTP header pair used by HTTPHeaders / HTTPResponse: two 0x54 strings.
struct HeaderPair {
    HeaderString first;                                // +0x00
    HeaderString second;                               // +0x54
    HeaderPair() {}                                    // (storage only; not emitted)
    HeaderPair(const HeaderPair& o);                   // 0x00943650
    HeaderPair& operator=(const HeaderPair& o);        // 0x009436b0
};                                                     // 0xa8

typedef HeaderPair Job;   // same record type as the cookie vector element

// Cookie record moved through the HTTP client cookie list (0x40 bytes).
struct Cookie40 {
    int   m00;                                         // +0x00
    char  mPad04[0x1c - 4];
    void* mp1c;                                        // +0x1c
    int   m20;                                         // +0x20
    void* mp24;                                        // +0x24
    char  mPad28[0x40 - 0x28];
    Cookie40(const Cookie40& o);                       // 0x00942ce0
};

struct CookieNode {
    CookieNode* mpNext;                                // +0x00
    CookieNode* mpPrev;                                // +0x04
    Cookie40    mData;                                 // +0x08
};

struct CookieList {
    CookieNode* mpNode;                                // +0x00
    void insertAtNext(const Cookie40& src);            // 0x009435b0
};

// ------------------------------------------------------------------ HTTP headers / requests / clients

// Vector of HeaderPair (0xa8 stride) with an inline buffer at +0x18.
struct HeaderVec {
    HeaderPair* mpBegin;                               // +0x00
    HeaderPair* mpEnd;                                 // +0x04
    HeaderPair* mpCapacity;                            // +0x08
    int         m0c;                                   // +0x0c
    HeaderPair* mpSelf;                                // +0x10
    int         m14;                                   // +0x14
    char        mBuffer[0xa80];                        // +0x18

    void init() { mpSelf = (HeaderPair*)mBuffer; mpBegin = mpSelf; mpEnd = mpSelf; mpCapacity = mpSelf + (0xa80 / 0xa8); }

    HeaderPair* erase(HeaderPair* pos);                // 0x00944850
    void        insert(HeaderPair* pos, const HeaderPair& v);  // 0x009448c0
    void        push_back_empty();                     // 0x00944af0
};

// HTTPHeaders: a header-vector member used by the various Add/Remove helpers.
struct HTTPHeaders {
    HeaderVec mHeaders;                                // +0x00

    bool RemoveHeaderEntryWorker(const char* pField, int nWhich);   // 0x00944a30
    bool RemoveHeaderEntry(int field, int nWhich);                  // 0x00944ac0
    bool AddHeaderEntry(const char* pValue, const char** ppValue);  // 0x00944cb0
    bool AddHeaderEntryV(const char* pValue, const char* pV2);      // 0x00944d00
    bool AddHeaderEntryField(int field, const char** ppValue);      // 0x00944d50
    bool AddHeaderEntryFieldV(int field, const char* pV2);          // 0x00944db0
};

// HTTPResponse (used by Clear).
struct HTTPResponse {
    char mPad000[0x008];
    SsoString200 mStr08;                               // +0x008
    SsoString200 mStr21c;                              // +0x21c
    int  m430;                                         // +0x430
    int  m434;                                         // +0x434
    int  m438;                                         // +0x438
    int  m43c;                                         // +0x43c
    eastl::sso_string<0x50> mStr440;                   // +0x440 (0x64)
    HeaderVec mHeaderArray;                            // +0x4a4
    int  mF3c;                                         // +0xf3c

    void Clear();                                      // 0x00944bd0
};

// A report/response cookie record (0x30 in the client cookie callbacks).
struct CookieJob {
    char  mPad00[0x0c];
    SsoString10 mStr0c;                                // +0x0c
    u16   m1c;                                         // +0x1c
    int   m20;                                         // +0x20
    char  b28;                                         // +0x28
    void* mp2c;                                        // +0x2c
};

// ------------------------------------------------------------------ client / request classes

class HTTPClient;

// UTFInternet::HTTPRequest (size 0xd98).  Note: distinct from the 0x943de0 request.
struct UTFHTTPRequest {
    void*       mpVtbl;                                // +0x000
    int         mnRefCount;                            // +0x004
    SsoString10 mMethod;                               // +0x008 (0x24)
    int         m2c;                                   // +0x02c
    URLClass    mURL;                                  // +0x030
    SsoString200 mStr0e0;                              // +0x0e0
    HeaderVec   mVec2f4;                               // +0x2f4 (job vector, 0xa98)
    void*       mpD8c;                                 // +0xd8c
    void*       mpD90;                                 // +0xd90
    void*       mpD94;                                 // +0xd94

    void Construct();                                  // 0x009442e0
    void Destroy();                                    // 0x00944380
    bool AddRequestParameter(const char* pName, const char* pValue);   // 0x00944660
    bool AddRequestParameterStr(const HeapString& name, const HeapString& value);  // 0x00944a10 (thunk)
};

// One of the HTTPClient's worker/filter sub-objects (vtable + refcount at +4).
struct RefObj90 {
    void* mpVtbl;                                      // +0x00
    int   mnRefCount;                                  // +0x04
};

extern "C" {
void __cdecl JobDestroyRange(HeaderPair* first, HeaderPair* last);      // 0x00943420
HeaderPair* __cdecl CopyJob(HeaderPair* first, HeaderPair* last, HeaderPair* dst);   // 0x009437a0
HeaderPair* __cdecl UninitializedCopyJob(HeaderPair* first, HeaderPair* last, HeaderPair* dst);  // 0x00943710
HeaderPair* __cdecl JobDestroyRangeDst(HeaderPair* first, HeaderPair* last, HeaderPair* dst);    // 0x00943500
HeaderPair* __cdecl CopyBackwardJob(HeaderPair* first, HeaderPair* last, HeaderPair* dst);       // 0x00943830
// ListDestroy / FUN_0094cf40 / Mutex_dtor are __thiscall (this in ecx); the thin
// casts below let the call sites pass the pointer in ecx as the original does.
extern "C" void __cdecl ListDestroy(void* p);                            // 0x00943480
typedef void (__thiscall *ListDestroyThis)(CookieList*);
void __cdecl FUN_0094d230();
extern "C" void __cdecl FUN_0094cf40(void* p);                           // 0x0094cf40
typedef void (__thiscall *FUN_0094cf40This)(void*);
void __cdecl FUN_0060a100(HeapString* s);
void __cdecl FUN_0060a150(void* s, const char* first, const char* last);
void __cdecl FUN_0060a2c0(void* s, const char* first, const char* last);
void __cdecl FUN_00919a40(HeapString* s);
void __cdecl FUN_00530670(HeapString* s);
void __cdecl FUN_0061c280(HeapString* s, u32 n);
int  __cdecl FUN_00607580(HeapString* s, char c, u32 pos);
void __cdecl FUN_00943a30();
void __cdecl FUN_009421b0();
void __cdecl FUN_0091c280();
}

// EA::Thread::Mutex ctor/dtor.
extern "C" void __cdecl Mutex_ctor(EA::Thread::Mutex* m, const void* params, bool lock); // 0x009222a0
extern "C" void __cdecl Mutex_dtor(EA::Thread::Mutex* m);                                 // 0x00922130
typedef void (__thiscall *Mutex_dtorThis)(EA::Thread::Mutex*);
extern "C" void __cdecl Mutex_LockPtr(EA::Thread::Mutex* m, const void* t);               // 0x009221b0
extern "C" void __cdecl Mutex_UnlockPtr(EA::Thread::Mutex* m);                            // 0x00922270

// eastl RangeInitialize for the method string.
extern "C" void __cdecl RangeInitialize(HeapString* s, u32 n);       // 0x00475ab0

// HTTPRequest helpers.
extern "C" void __cdecl HTTPRequestBase_SetMethod(void* req, int method);   // 0x009438c0
extern "C" void __cdecl UrlHolder_SetURL(void* holder, const char* url);    // 0x00942f70

// HTTPClient::Shutdown (already defined above as HTTPClient::Shutdown()).

// ---------------------------------------------------------------------------
// @ 0x00943f60  EA::Internet::HTTPClient::HTTPClient  (ecx = this)
// ---------------------------------------------------------------------------
class HTTPClientCtor {
public:
    void ctor();
};

void HTTPClientCtor::ctor() {
    char* self = (char*)this;
    *(void**)(self + 0x00) = (void*)0x143ef0c;
    *(void**)(self + 0x04) = (void*)0x13fb19c;
    _InterlockedExchange((volatile long*)(self + 0x08), 0);
    *(void**)(self + 0x00) = (void*)0x143f240;
    *(void**)(self + 0x04) = (void*)0x143f23c;
    *(u8*)(self + 0x0c)   = 0;
    *(u32*)(self + 0x10)  = 0;
    *(u32*)(self + 0x14)  = 0;
    *(u32*)(self + 0x18)  = 0;
    *(u32*)(self + 0x1c)  = 0;
    RangeInitialize((HeapString*)(self + 0x14), 0x14);
    char* p = *(char**)(self + 0x14);
    // "EA/2.0 (compatible)" (0x13 bytes) copied into the freshly-allocated buffer.
    const char* kAgent = "EA/2.0 (compatible)";
    for (int i = 0; i < 0x13; ++i)
        p[i] = kAgent[i];
    *(u32*)(self + 0x18) = (u32)(p + 0x13);
    p[0x13] = 0;
    *(u32*)(self + 0x24) = 0;
    *(u32*)(self + 0x28) = 0;
    *(u32*)(self + 0x2c) = 0;
    *(u32*)(self + 0x30) = 0;
    *(u32*)(self + 0x34) = (u32)kVtblEmpty8;
    *(u32*)(self + 0x38) = (u32)kVtblEmpty8;
    *(u32*)(self + 0x3c) = (u32)kVtblEmpty16;
    *(u32*)(self + 0x44) = (u32)kVtblEmpty8;
    *(u32*)(self + 0x48) = (u32)kVtblEmpty8;
    *(u32*)(self + 0x4c) = (u32)kVtblEmpty16;
    *(u32*)(self + 0x54) = 0;
    *(u32*)(self + 0x58) = 0;
    Mutex_ctor((EA::Thread::Mutex*)(self + 0x60), 0, true);
    *(u32*)(self + 0x90) = 0;
    *(u32*)(self + 0x94) = (u32)(self + 0x94);
    *(u32*)(self + 0x98) = (u32)(self + 0x94);
    FUN_0094d230();
    *(u32*)(self + 0xfc) = 0;
    *(u16*)(self + 0xfa) = 0;
    *(u16*)(self + 0xf8) = 2;
    *(u32*)(self + 0x114) = (u32)kVtblEmpty8;
    *(u32*)(self + 0x118) = (u32)kVtblEmpty8;
    *(u32*)(self + 0x11c) = (u32)kVtblEmpty8b;
    *(u16*)(self + 0x124) = 0;
    *(u32*)(self + 0x128) = 0xf;
    *(u32*)(self + 0x130) = 0;
    *(u32*)(self + 0x134) = 0;
    *(u32*)(self + 0x138) = 0;
    *(u32*)(self + 0x13c) = 0;
    *(u32*)(self + 0x140) = 0;
    *(u32*)(self + 0x144) = 0x400;
    *(u32*)(self + 0x148) = 0;
    *(u32*)(self + 0x14c) = 0x400;
    *(u32*)(self + 0x150) = 0;
    *(u32*)(self + 0x154) = 0;
    *(u32*)(self + 0x158) = 0;
}

// ---------------------------------------------------------------------------
// @ 0x00944250  eastl::basic_string<char>::push_back(char)  (ecx = string, ret 4)
// ---------------------------------------------------------------------------
void HeapString::push_back(char c) {
    if (mpEnd + 1 == mpCapacity) {
        u32 size   = (u32)(mpCapacity - mpBegin);
        u32 newLen = (u32)(mpEnd - mpBegin) + 1;
        u32 cap    = size - 1;
        if (cap < 9)
            cap = 8;
        else
            cap = cap * 2;
        u32 want = (newLen <= cap) ? cap : newLen;
        u32 cur  = (u32)(mpEnd - mpBegin);
        u32 low  = (cur <= want) ? cur : want;
        if (size < low + 1)
            sso_grow(this, low + 1);
    }
    *mpEnd = c;
    ++mpEnd;
    *mpEnd = 0;
}

// ---------------------------------------------------------------------------
// @ 0x009442e0  UTFInternet::HTTPRequest::HTTPRequest  (ecx = this)
// ---------------------------------------------------------------------------
void UTFHTTPRequest::Construct() {
    *(void**)this = (void*)0x13fb19c;
    _InterlockedExchange((volatile long*)&mnRefCount, 0);
    *(void**)this = (void*)0x143f258;
    mMethod.init();
    m2c = 0;
    mURL.Construct();
    mStr0e0.init();
    mVec2f4.init();
    mpD8c = 0;
    mpD90 = 0;
    mpD94 = 0;
}

// ---------------------------------------------------------------------------
// @ 0x00944380  UTFInternet::HTTPRequest::~HTTPRequest  (ecx = this)
// ---------------------------------------------------------------------------
void UTFHTTPRequest::Destroy() {
    if (mpD90 != 0)
        ((void(__thiscall*)(void*))((*(void***)mpD90)[2]))(mpD90);
    if (mpD8c != 0)
        ((void(__thiscall*)(void*))((*(void***)mpD8c)[2]))(mpD8c);
    HeaderVec* v = &mVec2f4;
    JobDestroyRange(v->mpBegin, v->mpEnd);
    if (v->mpBegin != 0 && v->mpBegin != v->mpSelf)
        operator_delete__(v->mpBegin);
    mStr0e0.Destroy();
    mURL.Destroy();
    mMethod.Destroy();
    *(void**)this = (void*)0x13fb19c;
}

// ---------------------------------------------------------------------------
// @ 0x00944450  EA::Internet::HTTPRequest::CreateHTTPGetRequest
//   static: arg1 = const char* url, arg2 = filter object, arg3 = UTFHTTPRequest** out
// ---------------------------------------------------------------------------
bool __cdecl CreateHTTPGetRequest(const char* pURL, void* pFilter, UTFHTTPRequest** ppOut) {
    if (ppOut == 0)
        return false;
    UTFHTTPRequest* req = (UTFHTTPRequest*)eastl_allocate(0xd98, "UTFInternet/HTTPRequest", 0, 0, 0, 0);
    if (req != 0) {
        req->Construct();
        if (req != 0)
            _InterlockedIncrement((volatile long*)&req->mnRefCount);
    }
    _InterlockedIncrement((volatile long*)&req->mnRefCount);
    HTTPRequestBase_SetMethod(req, 2);
    req->mURL.SetURL(pURL, true);
    HeapString* pStr = req->mURL.GetString();
    const char* last  = pStr->mpEnd;
    HeapString* pStr2 = req->mURL.GetString();
    const char* first = pStr2->mpBegin;
    FUN_0060a2c0(&req->mStr0e0, first, last);
    if (pFilter != req->mpD90) {
        if (pFilter != 0)
            ((void(__thiscall*)(void*))((*(void***)pFilter)[1]))(pFilter);
        void* old = req->mpD90;
        req->mpD90 = pFilter;
        if (old != 0)
            ((void(__thiscall*)(void*))((*(void***)old)[2]))(old);
    }
    *ppOut = req;
    {
        long old = _InterlockedExchangeAdd((volatile long*)&req->mnRefCount, -1);
        if (old - 1 == 0) {
            _InterlockedExchange((volatile long*)&req->mnRefCount, 1);
            ((void(__thiscall*)(void*, int))((*(void***)req)[0]))(req, 1);
        }
    }
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x00944570  EA::Internet::HTTPClient::~HTTPClient  (ecx = this)
// ---------------------------------------------------------------------------
// Wide (UTF-16) heap string: 3 pointers + allocator pad; Destroy uses the 2-byte
// element-stride check (`(cap - begin) & ~1 > 2`).
struct WideString {
    wchar_t* mpBegin;                                  // +0x00
    wchar_t* mpEnd;                                    // +0x04
    wchar_t* mpCapacity;                               // +0x08
    int      mAllocator;                               // +0x0c
    void Destroy() {
        if (((int)((char*)mpCapacity - (char*)mpBegin) & ~1) > 2 && mpBegin != 0)
            operator_delete__(mpBegin);
    }
};

typedef struct HTTPClientEx HTTPClientEx;
struct HTTPClientEx {
    void*       mpVtbl;                                // +0x000
    void*       mpVtbl2;                               // +0x004
    char        mPad008[0x0c - 0x08];
    bool        mbInitialized;                         // +0x00c
    u32         m10;                                   // +0x010
    HeapString  mAgent;                                // +0x014 (agent string)
    HeapString  m24;                                   // +0x024
    WideString  m34;                                   // +0x034 (wide)
    WideString  m44;                                   // +0x044 (wide)
    RefObj90*   mp54;                                  // +0x054
    RefObj90*   mp58;                                  // +0x058
    char        mPad05c[0x060 - 0x05c];
    EA::Thread::Mutex mMutex;                          // +0x060
    char        mPad090[0x090 - 0x061];
    void*       mpWorkerInfo;                          // +0x090
    CookieList  mCookieList;                           // +0x094
    char        mCListA0[0x114 - 0x098];               // +0x098 (opaque list)
    HeapString  m114;                                  // +0x114
    char        mPad124[0x150 - (0x114 + 0x10)];       // +0x124
    void*       mp150;                                 // +0x150

    void Destroy();                                    // 0x00944570
    bool AddCookie(CookieJob* pJob, char bKeep);       // 0x00944e10
};

void HTTPClientEx::Destroy() {
    mpVtbl  = (void*)0x143f240;
    mpVtbl2 = (void*)0x143f23c;
    ((HTTPClient*)this)->Shutdown();
    if (mp150 != 0) {
        if (*(int*)((char*)mp150 - 4) != 0)
            operator_delete__(mp150);
    }
    m114.Destroy();
    (*(FUN_0094cf40This)FUN_0094cf40)((char*)this + 0xa0);
    (*(ListDestroyThis)ListDestroy)(&mCookieList);
    (*(Mutex_dtorThis)Mutex_dtor)(&mMutex);
    if (mp58 != 0)
        ((void(__thiscall*)(void*))((*(void***)mp58)[2]))(mp58);
    if (mp54 != 0)
        ((void(__thiscall*)(void*))((*(void***)mp54)[2]))(mp54);
    m44.Destroy();
    m34.Destroy();
    mAgent.Destroy();
    mpVtbl2 = (void*)0x13fb19c;
    mpVtbl  = (void*)0x13eb938;
}

// HTTPRequest::SetURL internal (called with the request; it forwards to the URL at +0x30).
extern "C" void __cdecl HTTPRequest_SetURL(void* req, const char* url);   // 0x00942f70

// ---------------------------------------------------------------------------
// @ 0x00944660  UTFInternet::HTTPRequest::AddRequestParameter
//   (ecx = this, arg1 = const char* name, arg2 = const char* value, ret 8)
// ---------------------------------------------------------------------------
bool UTFHTTPRequest::AddRequestParameter(const char* pName, const char* pValue) {
    HeapString* url = mURL.GetString();
    if (url->mpBegin == url->mpEnd || pName == 0 || *pName == 0)
        return false;

    SsoString200 line;
    line.init();
    int hash = (int)FUN_00607580(url, '#', 0);
    const char* hashEnd;
    if (hash == -1)
        hashEnd = url->mpEnd;
    else
        hashEnd = url->mpBegin + hash;
    FUN_0060a2c0(&line, url->mpBegin, hashEnd);

    int q = (int)FUN_00607580(url, '?', 0);
    char sep = (q == -1) ? '&' : '?';
    line.push_back(sep);
    line.append(pName, pName + strlen(pName));
    line.push_back('=');

    if (pValue != 0 && *pValue != 0) {
        SsoString200 enc;
        enc.mpBegin = kVtblEmpty8;
        enc.mpEnd   = kVtblEmpty8;
        enc.mPad0c  = (int)kVtblEmpty8b;
        FUN_0047c600((u32)(strlen(pValue) * 3));
        if (!URL_ConvertPathToEncodedForm(pValue, &enc, 0)) {
            enc.Destroy();
            line.DeallocateSelf();
            return false;
        }
        line.append(enc.mpBegin, enc.mpEnd);
        enc.Destroy();
    }

    if (hash != -1)
        line.append(url->mpBegin + hash, url->mpEnd);

    HTTPRequest_SetURL(this, line.mpBegin);
    line.Destroy();
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x00944850  eastl::vector<pair<StrStub,StrStub>>::erase (ecx = vec, ret 4)
// ---------------------------------------------------------------------------
HeaderPair* HeaderVec::erase(HeaderPair* pos) {
    if ((char*)pos + 0xa8 < (char*)mpEnd)
        CopyJob((HeaderPair*)((char*)pos + 0xa8), mpEnd, pos);
    mpEnd = (HeaderPair*)((char*)mpEnd - 0xa8);
    HeaderPair* last = mpEnd;
    last->second.Destroy();
    last->first.Destroy();
    return pos;
}

// ---------------------------------------------------------------------------
// @ 0x009448c0  eastl::vector<pair<StrStub,StrStub>>::insert (ecx = vec, ret 8)
// ---------------------------------------------------------------------------
void HeaderVec::insert(HeaderPair* pos, const HeaderPair& v) {
    HeaderPair* end = mpEnd;
    if (end != mpCapacity) {
        if (end != 0)
            new ((HeaderPair*)((char*)end - 0xa8)) HeaderPair(*(HeaderPair*)((char*)end - 0xa8));
        CopyBackwardJob(pos, (HeaderPair*)((char*)end - 0xa8), end);
        *pos = v;
        mpEnd = (HeaderPair*)((char*)mpEnd + 0xa8);
        return;
    }
    u32 count = (u32)(((char*)end - (char*)mpBegin) / 0xa8);
    u32 newCap;
    if (count == 0)
        newCap = 1;
    else
        newCap = count * 2;
    HeaderPair* newBuf;
    if (newCap == 0)
        newBuf = 0;
    else
        newBuf = (HeaderPair*)operator_new(newCap * 0xa8, kEastlName, 0, 0, kEastlFile, 0xd1);
    HeaderPair* p = UninitializedCopyJob(mpBegin, pos, newBuf);
    JobDestroyRangeDst(mpBegin, pos, newBuf);
    if (p != 0)
        new (p) HeaderPair(v);
    HeaderPair* mid = (HeaderPair*)((char*)p + 0xa8);
    HeaderPair* end2 = UninitializedCopyJob(pos, mpEnd, mid);
    JobDestroyRangeDst(pos, mpEnd, mid);
    if (mpBegin != 0 && mpBegin != mpSelf)
        operator_delete__(mpBegin);
    mpBegin = newBuf;
    mpEnd = end2;
    mpCapacity = (HeaderPair*)((char*)newBuf + newCap * 0xa8);
}

// ---------------------------------------------------------------------------
// @ 0x00944a10  UTFInternet::HTTPRequest::AddRequestParameterStr (thunk)
// ---------------------------------------------------------------------------
bool UTFHTTPRequest::AddRequestParameterStr(const HeapString& name, const HeapString& value) {
    const char* v = value.mpBegin;
    const char* n = name.mpBegin;
    return AddRequestParameter(n, v);
}

// ---------------------------------------------------------------------------
// @ 0x00944a30  EA::Internet::HTTPHeaders::RemoveHeaderEntryWorker (ret 8)
// ---------------------------------------------------------------------------
bool HTTPHeaders::RemoveHeaderEntryWorker(const char* pField, int nWhich) {
    int count = 0;
    if (pField != 0) {
        if ((int)strlen(pField) != 0) {
            HeaderPair* it = mHeaders.mpBegin;
            if (it != mHeaders.mpEnd) {
                do {
                    if (_stricmp(it->first.mpBegin, pField) == 0) {
                        if (count == nWhich) {
                            mHeaders.erase(it);
                            return true;
                        }
                        ++count;
                    }
                    it = (HeaderPair*)((char*)it + 0xa8);
                } while (it != mHeaders.mpEnd);
            }
            return false;
        }
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x00944ac0  EA::Internet::HTTPHeaders::RemoveHeaderEntry (ret 8)
// ---------------------------------------------------------------------------
bool HTTPHeaders::RemoveHeaderEntry(int field, int nWhich) {
    return RemoveHeaderEntryWorker((const char*)HeaderFieldToFieldString(field), nWhich);
}

// ---------------------------------------------------------------------------
// @ 0x00944af0  eastl::vector<pair<StrStub,StrStub>>::push_back (empty header)
// ---------------------------------------------------------------------------
void HeaderVec::push_back_empty() {
    HeaderPair* end = mpEnd;
    if (end < mpCapacity) {
        mpEnd = (HeaderPair*)((char*)end + 0xa8);
        if (end != 0) {
            end->first.init();
            end->second.init();
        }
        return;
    }
    HeaderPair tmp;
    tmp.first.init();
    tmp.second.init();
    insert(end, tmp);
    tmp.first.Destroy();
    tmp.second.Destroy();
}

// ---------------------------------------------------------------------------
// @ 0x00944bd0  EA::Internet::HTTPResponse::Clear  (ecx = this)
// ---------------------------------------------------------------------------
void HTTPResponse::Clear() {
    if (mStr08.mpBegin != mStr08.mpEnd) {
        *mStr08.mpBegin = 0;
        mStr08.mpEnd = mStr08.mpBegin;
    }
    if (mStr21c.mpBegin != mStr21c.mpEnd) {
        *mStr21c.mpBegin = 0;
        mStr21c.mpEnd = mStr21c.mpBegin;
    }
    m430 = 0;
    m434 = -1;
    m438 = -1;
    m43c = 0;
    if (mStr440.mpBegin != mStr440.mpEnd) {
        *mStr440.mpBegin = 0;
        mStr440.mpEnd = mStr440.mpBegin;
    }
    HeaderPair* b = mHeaderArray.mpBegin;
    HeaderPair* e = mHeaderArray.mpEnd;
    CopyJob(e, e, b);
    JobDestroyRange(b, e);
    mHeaderArray.mpEnd = (HeaderPair*)((char*)mHeaderArray.mpEnd
        - (u32)(((char*)e - (char*)b) / 0xa8) * 0xa8);
    if (mF3c != 0) {
        void* p = (void*)mF3c;
        mF3c = 0;
        ((void(__thiscall*)(void*))((*(void***)p)[2]))(p);
    }
}

// ---------------------------------------------------------------------------
// @ 0x00944cb0  EA::Internet::HTTPHeaders::AddHeaderEntry (ret 8)
// ---------------------------------------------------------------------------
bool HTTPHeaders::AddHeaderEntry(const char* pValue, const char** ppValue) {
    if (pValue == 0 || *pValue == 0)
        return false;
    mHeaders.push_back_empty();
    ((HeaderPair*)((char*)mHeaders.mpEnd - 0xa8))->first.assign(pValue);
    ((HeaderString*)((char*)mHeaders.mpEnd - 0x54))->assign(*ppValue);
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x00944d00  EA::Internet::HTTPHeaders::AddHeaderEntryV (nullable value, ret 8)
// ---------------------------------------------------------------------------
bool HTTPHeaders::AddHeaderEntryV(const char* pValue, const char* pV2) {
    if (pValue == 0 || *pValue == 0)
        return false;
    mHeaders.push_back_empty();
    ((HeaderPair*)((char*)mHeaders.mpEnd - 0xa8))->first.assign(pValue);
    if (pV2 != 0)
        ((HeaderString*)((char*)mHeaders.mpEnd - 0x54))->assign(pV2);
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x00944d50  EA::Internet::HTTPHeaders::AddHeaderEntryField (by field id, ret 8)
// ---------------------------------------------------------------------------
bool HTTPHeaders::AddHeaderEntryField(int field, const char** ppValue) {
    const char* name = HeaderFieldToFieldString(field);
    if (name == 0 || *name == 0)
        return false;
    mHeaders.push_back_empty();
    ((HeaderPair*)((char*)mHeaders.mpEnd - 0xa8))->first.assign(name);
    ((HeaderString*)((char*)mHeaders.mpEnd - 0x54))->assign(*ppValue);
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x00944db0  EA::Internet::HTTPHeaders::AddHeaderEntryFieldV (by id, nullable, ret 8)
// ---------------------------------------------------------------------------
bool HTTPHeaders::AddHeaderEntryFieldV(int field, const char* pV2) {
    const char* name = HeaderFieldToFieldString(field);
    if (name == 0 || *name == 0)
        return false;
    mHeaders.push_back_empty();
    ((HeaderPair*)((char*)mHeaders.mpEnd - 0xa8))->first.assign(name);
    if (pV2 != 0)
        ((HeaderString*)((char*)mHeaders.mpEnd - 0x54))->assign(pV2);
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x00944e10  EA::Internet::HTTPClient::AddCookie (ecx = client, ret 8)
// ---------------------------------------------------------------------------
extern "C" void __cdecl FUN_0061e200(SsoString10* s, u32 pos, u32 n);   // erase
extern "C" void __cdecl FUN_009421b0_1(void* p);                        // Pump

// The report/response worker carried by a cookie record (pointer at +0x2c of the record).
struct CookieWorker {
    int   m00;                                         // +0x00
    int   m04;                                         // +0x04
    char  mPad08[0x10 - 0x08];
    int   m10;                                         // +0x10
    int   m14;                                         // +0x14
    char  mPad18[0x1c - 0x18];
    void* mp1c;                                        // +0x1c (the request)
    void* mp20;                                        // +0x20
    void* mp24;                                        // +0x24 (the HTTPResponse)
};

bool HTTPClientEx::AddCookie(CookieJob* pJob, char bKeep) {
    if (pJob == 0)
        return false;
    CookieWorker* w = (CookieWorker*)pJob->mp2c;
    if (w == 0)
        return false;
    if (w->m10 > 2)
        return false;
    if (w->m04 != 5)
        return false;
    if (pJob->b28 == 0)
        return false;

    ++w->m10;
    w->m14 = 0;
    w->m04 = 1;

    UTFHTTPRequest* req = (UTFHTTPRequest*)w->mp1c;
    if (req != 0) {
        void* r1 = req->mpD8c;
        if (r1 != 0 && !((bool(__thiscall*)(void*, int, int))((*(void***)r1)[0x28 / 4]))(r1, 0, 0))
            return false;
        void* r2 = req->mpD90;
        if (r2 != 0) {
            if (!((bool(__thiscall*)(void*, int, int))((*(void***)r2)[0x28 / 4]))(r2, 0, 0))
                return false;
            if (!((bool(__thiscall*)(void*, int))((*(void***)r2)[0x20 / 4]))(r2, 0))
                return false;
        }
    }
    if (w->mp24 != 0)
        ((HTTPResponse*)w->mp24)->Clear();
    Mutex_LockPtr(&mMutex, &kLockTimeout);
    mCookieList.insertAtNext(*(Cookie40*)&pJob[0]);
    Mutex_UnlockPtr(&mMutex);

    if (bKeep) {
        FUN_0061e200(&pJob->mStr0c, 0, 0xffffffff);
        pJob->m1c = 0;
        FUN_009421b0_1((void*)pJob->m20);
    }
    return true;
}

}}
