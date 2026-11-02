// src/game/UTFSpore_Win32/_at_00900000.cpp -- migrated from slice(s) s00903400, s00902460, s009013e0, s008ff610 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/_at_00900000.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Allocator/ICoreAllocator.h"

// unnamed retail callees and globals (address in the comment)
extern uint16_t gEmptyStrBuf[1];   // 0x01667bac
extern unsigned gNextRequestId;    // 0x0154db08
#include <string.h>
#include <new>
#include <intrin.h>
#include "EA/XML/XmlTextWriter.h"
#include <stdarg.h>
#include "EA/IO/IStream.h"
#include "EA/IO/MemoryStream.h"

// ---- items of slice s008ff610 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct IUnk {
    virtual void AddRef();
    virtual void Release();
};
struct IRC {  // refcounted interface (dtor, AddRef, Release)
    virtual void v0(int);
    virtual void AddRef();
    virtual void Release();
};
struct ResourceRequest;
typedef void (__cdecl *ReqCb)(void* evt, void* ctx);
struct ILogListener;
extern uint16_t gEmptyStrBuf[1];   // 0x01667bac
extern unsigned gNextRequestId;    // 0x0154db08
struct ResourceRequest {
    ResourceRequest* mpNext;        // +0
    ResourceRequest* mpPrev;        // +4
    ILogListener* mpErrorListener;  // +8
    const uint16_t* mpURL;          // +0xc
    char* mTypeBegin;               // +0x10
    char* mTypeEnd;                 // +0x14
    char* mTypeCap;                 // +0x18
    int mTypePad;                   // +0x1c
    IUnk* mpResource;               // +0x20
    int mEncoding;                  // +0x24
    int mEncodingSource;            // +0x28
    bool mCacheable;                // +0x2c
    ReqCb mpCallback;               // +0x30
    void* mpContext;                // +0x34
    unsigned mRequestId;            // +0x38
    IRC* mpStream;                  // +0x3c

    ResourceRequest(const uint16_t* url, ILogListener* el);
    bool SetEncoding(int enc, int src);
};
// ---- items of slice s008ff610 end

// ---- items of slice s009013e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
#pragma intrinsic(wcslen)
struct ReaderRange {
    unsigned int m00;   // +0x00
    unsigned int m04;   // +0x04
    unsigned int m08;   // +0x08
    unsigned int m0c;   // +0x0c
    unsigned int m10;   // +0x10
    void FUN_00928c40(unsigned int v);   // 0x928c40
};
namespace EA {
namespace XML {
class XmlTextReader {
public:
    char          _pad00[0x10];
    ReaderRange   mRange;     // +0x10
    char          _pad24[0x14];
    int           m38;        // +0x38
    int           m3c;        // +0x3c
    int           m40;        // +0x40
    char          _pad44[0x28];
    void*         m6c;        // +0x6c
    char          _pad70[0x0c];
    int           m7c;        // +0x7c

    bool FUN_009013e0();                       // 0x9013e0
    void FUN_00901440(int a, int b);           // 0x901440
    void FUN_00901480(int a, int b, int c);    // 0x901480
    bool FUN_00901df0();                       // 0x901df0
    bool FUN_00901e40();                       // 0x901e40
    char FUN_00901340();                       // 0x901340 Read
    void FUN_00901220();                       // 0x901220 InitParser
    char FUN_00900a30(int a, int b);           // 0x900a30
    char FUN_00900610(int a, int b, int c);    // 0x900610
};
}
}
extern "C" size_t wcslen(const wchar_t*);
// ---- items of slice s009013e0 end

// ---- items of slice s00903400 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int   uint;
// ---- items of slice s00903400 end

// @ 0x00900310
ResourceRequest::ResourceRequest(const uint16_t* url, ILogListener* el)
{
    mpErrorListener = el;
    _ReadWriteBarrier();
    mpURL = url;
    _ReadWriteBarrier();
    mpPrev = 0;
    mpNext = 0;
    _ReadWriteBarrier();
    mTypeCap = (char*)gEmptyStrBuf + 1;
    _ReadWriteBarrier();
    mTypeBegin = (char*)gEmptyStrBuf;
    mTypeEnd = (char*)gEmptyStrBuf;
    mpResource = 0;
    _ReadWriteBarrier();
    mEncoding = 8;
    mEncodingSource = 4;
    mCacheable = true;
    mpCallback = 0;
    mpContext = 0;
    _ReadWriteBarrier();
    mRequestId = gNextRequestId;
    gNextRequestId += 1;
    mpStream = 0;
}

// @ 0x00901df0
namespace EA { namespace XML {
bool XmlTextReader::FUN_00901df0()
{
    int p = m38;
    if (p == 0)
        return false;
    if (m3c == 0) {
        m3c = p;
        m40 = p;
        while (*(int*)m3c != 0) {
            m3c = *(int*)m3c;
        }
    } else if (m40 != 0) {
        m40 = *(int*)m40;
    }
    return m40 != 0;
}
}}  // namespace EA::XML

// @ 0x00901e40
namespace EA { namespace XML {
bool XmlTextReader::FUN_00901e40()
{
    if (m38 == 0)
        return false;
    if (m3c == 0)
        return false;
    return m40 != 0;
}
}}  // namespace EA::XML

// @ 0x009032e0
void FUN_009032e0(int* p, int v)
{
    if (p[1] == p[0]) { p[0] = v; p[1] = v; }
    else p[0] = v;
}

// @ 0x00903300
void FUN_00903300(char* p, int a, int b)
{
    *(int*)(p + 0x34) = a;
    *(int*)(p + 0x38) = b;
}

// @ 0x00903320
void FUN_00903320(char* p, int v)
{
    *(int*)(p + 0x3c) = v;
}

// @ 0x00903330
void FUN_00903330(char* p, int v)
{
    *(int*)(p + 0x40) = v;
}

// @ 0x00903340
void FUN_00903340(char* p, int v)
{
    *(int*)(p + 0x44) = v;
}

// @ 0x00903350
void FUN_00903350(char* p, int v)
{
    *(int*)(p + 0x50) = v;
    *(char*)(p + 0x134) = 1;
}

// @ 0x00903370
void FUN_00903370(char* p, int a, int b)
{
    *(int*)(p + 0x54) = a;
    *(int*)(p + 0x58) = b;
}

// @ 0x009033d0
int FUN_009033d0(char* p, int v)
{
    int t = *(int*)(p + 0x1e0);
    if (t == 1 || t == 3)
        return 0;
    *(int*)(p + 0x1ec) = v;
    return 1;
}

// @ 0x00903550
int XmlSetParsingState(char* state, char final)
{
    if (*(int*)(state + 0x1e0) == 2) {
        *(int*)(state + 0x11c) = 0x24;
        return 0;
    }
    if (*(int*)(state + 0x1e0) == 3) {
        if (final != 0) {
            *(int*)(state + 0x11c) = 0x21;
            return 0;
        }
    }
    else if (final != 0) {
        if (*(char*)(state + 0x1e8) != 0) {
            *(int*)(state + 0x11c) = 0x25;
            return 0;
        }
        *(int*)(state + 0x1e0) = 3;
        return 1;
    }
    *(int*)(state + 0x1e0) = 2;
    return 1;
}

// @ 0x009035d0
void XmlGetParsingStatus(char* state, int* out)
{
    out[0] = *(int*)(state + 0x1e0);
    out[1] = *(int*)(state + 0x1e4);
}

// @ 0x009035f0
int XmlGetByteIndex(char* state)
{
    if (*(int*)(state + 0x120) != 0)
        return (*(int*)(state + 0x24) - *(int*)(state + 0x28)) + *(int*)(state + 0x120);
    return -1;
}

// @ 0x00903610
int XmlFlushTailA(char* state)
{
    uint n = *(uint*)(state + 0x120);
    if (n != 0 && n >= *(uint*)(state + 0x128)) {
        char* self = *(char**)(state + 0x90);
        typedef void (__cdecl *ReportFn)(void*, uint, uint, void*);
        ((ReportFn)(*(void**)(self + 0x34)))(
            self, *(uint*)(state + 0x128), n, state + 0x198);
        *(uint*)(state + 0x128) = *(uint*)(state + 0x120);
    }
    return *(int*)(state + 0x198) + 1;
}

// @ 0x00903660
int XmlFlushTailB(char* state)
{
    uint n = *(uint*)(state + 0x120);
    if (n != 0 && n >= *(uint*)(state + 0x128)) {
        char* self = *(char**)(state + 0x90);
        typedef void (__cdecl *ReportFn)(void*, uint, uint, void*);
        ((ReportFn)(*(void**)(self + 0x34)))(
            self, *(uint*)(state + 0x128), n, state + 0x198);
        *(uint*)(state + 0x128) = *(uint*)(state + 0x120);
    }
    return *(int*)(state + 0x19c);
}
