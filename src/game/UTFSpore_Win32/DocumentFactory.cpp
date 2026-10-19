// src/game/UTFSpore_Win32/DocumentFactory.cpp -- migrated from slice(s) s008fc670 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/DocumentFactory.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/IO/FileStream.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void* __cdecl memcpy(void*, const void*, unsigned);
extern "C" int __cdecl strcmp(const char*, const char*);
extern const char* gMimeTextHtml;       // "text/html"
#include <intrin.h>
#pragma function(memcpy)
#pragma intrinsic(strcmp)

// ---- items of slice s008fc670 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" int __cdecl strcmp(const char*, const char*);
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
virtual void d0();
virtual void d1();
virtual void d2();
virtual void d3();
virtual void d4();
virtual void d5();
virtual void d6();
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
// ---- items of slice s008fc670 end

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
