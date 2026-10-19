// src/game/UTFSpore_Win32/ResourceRequest.cpp -- migrated from slice(s) s008ff610 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/ResourceRequest.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Allocator/ICoreAllocator.h"
#include <string.h>
#include <new>
#include <intrin.h>

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

// @ 0x009002f0
bool ResourceRequest::SetEncoding(int enc, int src)
{
    if (src <= mEncodingSource) {
        mEncodingSource = src;
        mEncoding = enc;
        return true;
    }
    return false;
}
