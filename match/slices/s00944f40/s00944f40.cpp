// Slice s00944f40: EA::Internet HTTP client worker helpers (MSVC 2008 SP1, /O2 /MD /Gy /TP /GS-).
//
//   00944f40  HTTPClient worker: build the request line + headers, then read the raw body
//   009453f0  HTTPClient worker: read the response status line and headers
//   009458c0  HTTPClient worker: re-issue the request after a redirect
//   00945a10  HTTPClient worker: map the HTTP status code to a job result
//   00945b20  EA::Internet::HTTPRequest::CreateHTTPPostRequest
//   00945c80  EA::Internet::HTTPClient::WriteRequestBody
//
// All six belong to the UTFSpore_Win32/HTTPClient.obj translation unit.  Only the two named
// functions exist in the retail symbol table; the four unnamed worker helpers are recovered from
// the call sites (thiscall members of EA::Internet::HTTPClient taking a WorkerThreadInfo*).
#include "types.h"

// ---------------------------------------------------------------------------------------------
// Callees (declared only; the originals live in the image / other TUs).
// ---------------------------------------------------------------------------------------------
extern "C" const char* __cdecl HeaderFieldToFieldString(int field);   // 0x00941c40
extern "C" char* __cdecl _ultoa(unsigned long value, char* buf, int radix);   // msvcr90
extern "C" void* __cdecl operator_new(unsigned int n, const char* type, int, int, int, int);  // 0x00F473A0
extern "C" void  __cdecl operator_delete__(void* p) throw();          // 0x00F47380
extern "C" int   __cdecl Sprintf8(char* buf, const char* fmt, ...);   // 0x00938470
extern "C" bool  __cdecl HTTPClientCheckTimeout(int job, int* timeout);      // 0x00942010
extern "C" void  __cdecl HTTPClientSendCallback(int sent, const char* buf, int n);  // 0x00942110
extern "C" bool  __cdecl Fn94ba30(const char* s);                     // 0x0094ba30
extern "C" const char* __cdecl GetPoliticalID(void* gameData);        // 0x0097e850
extern "C" void  __cdecl StrDtor(void* s);                            // 0x00530670
extern "C" void  __cdecl AtomicRefRelease(void* p);                   // 0x0060d210

static __forceinline const char* CharStrEnd(const char* p) {
    const char* e = p;
    while (*e) ++e;
    return e;
}

static int StrLen(const char* s) {
    return (int)(CharStrEnd(s) - s);
}

// Virtual-call helpers: the interfaces involved are only reachable through their vtable slot.
typedef void* (__thiscall *VF_This0)(void*);
typedef int   (__thiscall *VF_I0)(void*);
typedef int   (__thiscall *VF_I2)(void*, void*, int);
typedef int   (__thiscall *VF_I3)(void*, void*, int, int);
typedef bool  (__thiscall *VF_B0)(void*);
typedef bool  (__thiscall *VF_B1)(void*, int);
typedef bool  (__thiscall *VF_BS)(void*, void*);
typedef bool  (__thiscall *VF_B2)(void*, int, int);
#define VS(p, off) (*(void***)(p))[(off) / 4]

// ---------------------------------------------------------------------------------------------
// eastl::basic_string<char> head (three pointers).
// ---------------------------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------------------------
// eastl::fixed_string<char> local: string head + inline storage, so its address is self-relative.
// ---------------------------------------------------------------------------------------------
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
    void Append(const char* s) { append(s, CharStrEnd(s)); }
};

// ---------------------------------------------------------------------------------------------
// EA::Internet::URL (retail: lives at HTTPRequest+0x30).
// ---------------------------------------------------------------------------------------------
struct URL {
    Str* GetPart(int which);   // 0x0094baf0
    int  GetPort();            // 0x0094a4a0
    void SetURL(const char* url, bool flag);   // 0x0094a6a0
    void Fn94bb50(const char* location, char* out);   // 0x0094bb50
};

// ---------------------------------------------------------------------------------------------
// Request header list (retail: at HTTPRequest+0x2f4 and HTTPResponse+0x4a4).  Nodes are 0xa8 bytes.
// ---------------------------------------------------------------------------------------------
struct HeaderNode {
    Str   msName;       // +0x00
    char  pad0c[0x54 - 0x0c];
    Str   msValue;      // +0x54
    char  pad60[0xa8 - 0x60];
};
struct HeaderList {
    HeaderNode* mpBegin;   // +0x00
    HeaderNode* mpEnd;     // +0x04
    bool FindHeader(const char* name, void* out, int index);   // 0x00942050
    void AddHeaderPtr(int field, const void* v);               // 0x00944d50
    void AddHeaderStr(int field, const char* v);               // 0x00944db0
    void SetHeaderId(const char* field, int id);               // 0x00944a30
    void AddNode();                                            // 0x00944af0
};

// ---------------------------------------------------------------------------------------------
// UTFInternet::HTTPRequest (retail size 0xd98; URL at +0x30, header list at +0x2f4).
// ---------------------------------------------------------------------------------------------
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
    HeaderList* headers() { return (HeaderList*)((char*)this + 0x2f4); }
    void* ctor();                   // 0x009442e0
    void SetMethod(int m);          // 0x009438c0
    void SetURL(const char* u);     // 0x00942f70
    void Fn615c10(void* p);         // 0x00615c10
    void Fn615bd0(void* p);         // 0x00615bd0
};

struct Resp {
    char pad00[0x43c];
    int  mnStatus;     // +0x43c
    HeaderList* headers4a4() { return (HeaderList*)((char*)this + 0x4a4); }
    bool Clear();      // 0x00944bd0
};

struct Job {
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
    Job*   mpCurrentJob;             // +0x2c
};

// ---------------------------------------------------------------------------------------------
// Container stand-ins used by the worker helpers.
// ---------------------------------------------------------------------------------------------
struct Mutex { void Lock(unsigned timeout); void Unlock(); };   // 0x009221b0 / 0x00922270
struct CookieList { void insertAtNext(const void* src); };       // 0x009435b0
struct RawBuf { char pad[0x140]; };                              // 0x140 read buffer / write buffer base

// ---------------------------------------------------------------------------------------------
// HTTPClient proper.  Members below 0x168 mirror the retail layout.
// ---------------------------------------------------------------------------------------------
struct HTTPClient {
    char      pad00[0x0c];
    bool      mbInitialized;         // +0x0c
    char      pad0d[0x14 - 0x0d];
    Str       msUserAgent;           // +0x14
    char      pad20[0x60 - 0x20];
    Mutex     mMutex;                // +0x60
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

    CookieList* cookieList() { return (CookieList*)((char*)this + 0x94); }

    int  ReadRawBody(Info* info, char* buf);          // 0x00942290
    int  ReadResponseLine(Info* info, char* buf, int len, char flag);   // 0x009423d0
    int  ParseResponseStatus(Info* info);             // 0x00943bd0
    bool Fn944f40(Info* info);                        // 0x00944f40
    bool Fn9453f0(Info* info);                        // 0x009453f0
    bool Fn9458c0(Job* job);                          // 0x009458c0
    int  Fn945a10(Info* info);                        // 0x00945a10
    bool WriteRequestBody(Info* info);                // 0x00945c80
};

struct HTTPRequest {
    static bool CreateHTTPPostRequest(const char* url, void* body, void* image, Req** out);
};

// @ 0x00944f40
bool HTTPClient::Fn944f40(Info* info) {
    Job* job = info->mpCurrentJob;
    Req* req = job->mpRequest;
    HeaderList* hdr = req->headers();

    const char* userAgentField = HeaderFieldToFieldString(0x18);
    if (!hdr->FindHeader(userAgentField, 0, 0)) {
        if (msUserAgent.mpBegin != msUserAgent.mpEnd)
            hdr->AddHeaderPtr(0x18, &msUserAgent);
    }

    FStr s;
    s.Init();
    s.append(req->msMethod.mpBegin, CharStrEnd(req->msMethod.mpBegin));
    s.append(' ');

    if (msProxyServerAddress.mpBegin != msProxyServerAddress.mpEnd) {
        hdr->SetHeaderId(HeaderFieldToFieldString(0xe), 0);
        s.Append("http://");
        Str* part = req->url()->GetPart(3);
        s.append(part->mpBegin, CharStrEnd(part->mpBegin));
        int port = req->url()->GetPort();
        if (port != 0) {
            char buf[20];
            _ultoa(port, buf, 10);
            s.append(':');
            s.append(buf, CharStrEnd(buf));
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
                tmp.assignRange(part->mpBegin, CharStrEnd(part->mpBegin));
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
        p = req->url()->GetPart(5); s.append(p->mpBegin, CharStrEnd(p->mpBegin));
        p = req->url()->GetPart(6); s.append(p->mpBegin, CharStrEnd(p->mpBegin));
        p = req->url()->GetPart(7); s.append(p->mpBegin, CharStrEnd(p->mpBegin));
        p = req->url()->GetPart(8); s.append(p->mpBegin, CharStrEnd(p->mpBegin));
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
            s.append(node->msName.mpBegin, CharStrEnd(node->msName.mpBegin));
        }
        s.append((const char*)0x01420a80, (const char*)0x01420a82);
        s.append(node->msValue.mpBegin, CharStrEnd(node->msValue.mpBegin));
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
bool HTTPClient::Fn9453f0(Info* info) {
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
                HeaderList* list = resp->headers4a4();
                list->AddNode();
                HeaderNode* node = list->mpEnd - 1;
                node->msName.assignRange(name.mpBegin, CharStrEnd(name.mpBegin));
                node->msValue.assignRange(value.mpBegin, CharStrEnd(value.mpBegin));
                haveName = false;
            }
        } else if (firstField && mpReadBuffer[0] != ' ' && mpReadBuffer[0] != '\t') {
            if (haveName) {
                HeaderList* list = resp->headers4a4();
                list->AddNode();
                HeaderNode* node = list->mpEnd - 1;
                node->msName.assignRange(name.mpBegin, CharStrEnd(name.mpBegin));
                node->msValue.assignRange(value.mpBegin, CharStrEnd(value.mpBegin));
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
bool HTTPClient::Fn9458c0(Job* job) {
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
int HTTPClient::Fn945a10(Info* info) {
    Job* job = info->mpCurrentJob;
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
bool HTTPRequest::CreateHTTPPostRequest(const char* url, void* body, void* image, Req** out) {
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
    Sprintf8(buf, (const char*)0x013fc740, n);
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
bool HTTPClient::WriteRequestBody(Info* info) {
    Job* job = info->mpCurrentJob;
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
