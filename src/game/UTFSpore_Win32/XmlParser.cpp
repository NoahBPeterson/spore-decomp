// src/game/UTFSpore_Win32/XmlParser.cpp -- migrated from slice(s) s008e5320 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/XmlParser.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void  operator_delete__(void* p);
extern "C" int   XML_Parse(void* parser, const char* s, int len, int isFinal);
extern "C" void  XML_ParserFree(void* parser);
extern "C" void  XML_DefaultCurrent(void* parser);
#include <stddef.h>
#include <string.h>
#include <wchar.h>

// ---- items of slice s008e5320 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned short wchar16;
extern "C" void  operator_delete__(void* p);
extern "C" int   XML_Parse(void* parser, const char* s, int len, int isFinal);
extern "C" void  XML_ParserFree(void* parser);
extern "C" void  XML_DefaultCurrent(void* parser);
struct Flusher { void Fn8e4350(void* node); };  // 0x008e4350
struct DomNodeIface { virtual void fn0(); };
struct DomNodeBase  { void* Parent(); };   // 0x00ff0420 (thiscall)
struct Doc { void* Fn8e26e0(wchar16* s, int n, int flag); };  // 0x008e26e0
struct XmlParser {
    // +0    vftable
    // +4    mpDocument
    // +8/+0xc/+0x10  string begin/end/capacity
    // +0x18 pool begin
    // +0x21c mpParserNode
    // +0x220 mpXmlParser
    // +0x224 mbSpace
    // +0x228 mOffset
    // +0x22c..+0x42b  wchar buffer[256]
    // +0x430 counter
    // +0x434 index
    // +0x438 flag

    void  Fn8e5600(short* p, int n);                 // @ 0x008e5600
    int   Fn8e5a20(const char* s, int len, int fin); // 0x008e5a20
    void  Fn8e5730(void* parser, void* uri);         // @ 0x008e5730
    void  Fn8e59a0(char param2);                     // 0x008e59a0
    void  Fn8e5ca0();                                // @ 0x008e5ca0
    void  Fn8e5da0(wchar16* data, int count);        // @ 0x008e5da0
    void  Fn8e5fb0();                                // @ 0x008e5fb0
};
extern "C" void* Fn8e26e0(wchar16* s, int n, int flag);   // 0x008e26e0 (thiscall on Doc)
struct WStr { void push_back(short ch); };   // 0x008e5d10 (thiscall)
// ---- items of slice s008e5320 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" void* Fn8e26e0(wchar16* s, int n, int flag);   // 0x008e26e0 (thiscall on Doc)

// @ 0x008e59a0
__declspec(noinline) void XmlParser::Fn8e59a0(char param2)
{
    char* c = (char*)this;
    if (*(void**)(c + 0x21c) == 0) return;
    int n = (int)(*(wchar16**)(c + 0xc) - *(wchar16**)(c + 8));
    if (n == 0) return;
    wchar16* begin = *(wchar16**)(c + 8);
    if (param2 != 0) {
        if (n > 0) {
            wchar16* p = begin + n - 1;
            do {
                if (*p != 0x20) break;
                n--;
                p--;
            } while (n > 0);
        }
        begin[n] = 0;
    }
    if (n > 0) {
        void* r = ((Doc*)*(void**)(c + 4))->Fn8e26e0(begin, n, 1);
        ((Flusher*)*(void**)(c + 0x21c))->Fn8e4350(r);
    }
    if (*(wchar16**)(c + 8) != *(wchar16**)(c + 0xc)) {
        **(wchar16**)(c + 8) = 0;
        *(void**)(c + 0xc) = *(void**)(c + 8);
    }
}

// @ 0x008e5a20
int XmlParser::Fn8e5a20(const char* s, int len, int fin)
{
    char* c = (char*)this;
    int rc = 0;
    if (XML_Parse(*(void**)(c + 0x220), s, len, fin) == 0) {
        void* doc = *(void**)(c + 4);
        void* uri = *(void**)((char*)doc + 0x48);
        Fn8e5730(*(void**)(c + 0x220), uri);
        rc = 0;
    }
    *(int*)(c + 0x228) = *(int*)(c + 0x228) + len;
    return rc;
}

// @ 0x008e5a70
__declspec(noinline) void Fn8e5a70(void* p, void* a)
{ (void)a; *(volatile int*)p = 0; }

// @ 0x008e5b90
__declspec(noinline) void Fn8e5b90(void* p, void* a, void* b)
{ (void)a; (void)b; *(volatile int*)p = 0; }

// @ 0x008e5c50
void Fn8e5c50(void* parser)
{
    XmlParser* p = (XmlParser*)parser;
    char* c = (char*)p;
    p->Fn8e59a0(1);
    if (*(void**)(c + 0x21c) != 0) {
        ((DomNodeIface*)*(void**)(c + 0x21c))->fn0();
        void* parent = ((DomNodeBase*)*(void**)(c + 0x21c))->Parent();
        *(void**)(c + 0x21c) = parent;
    }
    *(char*)(c + 0x224) = 0;
    XML_DefaultCurrent(*(void**)(c + 0x220));
}

// @ 0x008e5ca0
void XmlParser::Fn8e5ca0()
{
    char* c = (char*)this;
    void* px = *(void**)(c + 0x220);
    *(void**)c = (void*)0x1437be4;
    if (px != 0) {
        XML_ParserFree(px);
        *(void**)(c + 0x220) = 0;
    }
    wchar16* b = *(wchar16**)(c + 8);
    wchar16* cap = *(wchar16**)(c + 0x10);
    if ((((char*)cap - (char*)b) & ~1) > 2 && b != 0 && b != *(wchar16**)(c + 0x18)) {
        operator_delete__(b);
    }
    *(void**)c = (void*)0x14357e4;
}

// @ 0x008e5da0
void XmlParser::Fn8e5da0(wchar16* data, int count)
{
    char* c = (char*)this;
    for (; count > 0; count--) {
        short s = (short)*data;
        if (s == 0x20 || s == 9 || s == 0xc || s == 0xd || s == 10 || s == 0x200b) {
            if (*(char*)(c + 0x224) == 0) {
                ((WStr*)(c + 8))->push_back(0x20);
                *(char*)(c + 0x224) = 1;
            }
        } else {
            ((WStr*)(c + 8))->push_back(s);
            *(char*)(c + 0x224) = 0;
        }
        data++;
    }
}

// @ 0x008e5e20
void Fn8e5e20(void* parser, wchar16* data, int count)
{
    XmlParser* p = (XmlParser*)parser;
    p->Fn8e5da0(data, count);
    XML_DefaultCurrent(*(void**)((char*)p + 0x220));
}

// @ 0x008e5ea0
__declspec(noinline) void* Fn8e5ea0(void* p, void* a)
{ (void)a; *(volatile int*)p = 0; return p; }

// @ 0x008e5fb0
__declspec(noinline) void XmlParser::Fn8e5fb0()
{ *(volatile int*)((char*)this + 0x220) = 0; }

// @ 0x008e60a0
__declspec(noinline) int Fn8e60a0(void* p, void* a, void* b)
{ (void)a; (void)b; *(volatile int*)p = 0; return 0; }
