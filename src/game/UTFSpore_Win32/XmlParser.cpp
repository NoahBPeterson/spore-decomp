// src/game/UTFSpore_Win32/XmlParser.cpp -- migrated from slice(s) s008e5320 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/XmlParser.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" void  operator_delete__(void* p);
extern "C" int   XML_Parse(void* parser, const char* s, int len, int isFinal);
extern "C" void  XML_ParserFree(void* parser);
extern "C" void  XML_DefaultCurrent(void* parser);
extern "C" void* FUN_0090af20(int);                        // 0x0090af20  parser create/wrapper
extern "C" int   FUN_00903b40(void*);                      // 0x00903b40  error code
extern "C" void  FUN_00903300(void*, void*, void*);        // 0x00903300  element handler
extern "C" void  FUN_00903320(void*, void*);               // 0x00903320  character data handler
extern "C" void  FUN_00903340(void*, void*);               // 0x00903340
extern "C" void  FUN_00903350(void*, void*);               // 0x00903350
extern "C" void  FUN_00903370(void*, void*, void*);        // 0x00903370
extern "C" void  FUN_009033b0(void*, void*);               // 0x009033b0
extern "C" void  FUN_009033c0(void*, void*);               // 0x009033c0
extern "C" void  FUN_009033d0(void*, int);                 // 0x009033d0
extern "C" void  FUN_009032e0(void*, void*);               // 0x009032e0  user data
extern "C" void  FUN_009035d0(void*, void*);               // 0x009035d0  get parsing status
extern "C" void* FUN_00903400(void*, int);                 // 0x00903400  get buffer
extern "C" int   FUN_00904580(void*, int, int);            // 0x00904580  parse buffer
extern "C" void  FUN_0090a870(void*, int);                 // 0x0090a870
#include <stddef.h>
#include <string.h>
#include <wchar.h>

// ---- items of slice s008e5320 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned short wchar16;
extern "C" void  operator_delete__(void* p);
extern "C" int   XML_Parse(void* parser, const char* s, int len, int isFinal);
extern "C" void  XML_ParserFree(void* parser);
extern "C" void  XML_DefaultCurrent(void* parser);
extern "C" void* FUN_0090af20(int);                        // 0x0090af20  parser create/wrapper
extern "C" int   FUN_00903b40(void*);                      // 0x00903b40  error code
extern "C" void  FUN_00903300(void*, void*, void*);        // 0x00903300  element handler
extern "C" void  FUN_00903320(void*, void*);               // 0x00903320  character data handler
extern "C" void  FUN_00903340(void*, void*);               // 0x00903340
extern "C" void  FUN_00903350(void*, void*);               // 0x00903350
extern "C" void  FUN_00903370(void*, void*, void*);        // 0x00903370
extern "C" void  FUN_009033b0(void*, void*);               // 0x009033b0
extern "C" void  FUN_009033c0(void*, void*);               // 0x009033c0
extern "C" void  FUN_009033d0(void*, int);                 // 0x009033d0
extern "C" void  FUN_009032e0(void*, void*);               // 0x009032e0  user data
extern "C" void  FUN_009035d0(void*, void*);               // 0x009035d0  get parsing status
extern "C" void* FUN_00903400(void*, int);                 // 0x00903400  get buffer
extern "C" int   FUN_00904580(void*, int, int);            // 0x00904580  parse buffer
extern "C" void  FUN_0090a870(void*, int);                 // 0x0090a870
struct Flusher { void Fn8e4350(void* node); };  // 0x008e4350
struct DomNodeIface { virtual void fn0(); };
struct DomNodeBase  { void* Parent(); };   // 0x00ff0420 (thiscall)
struct Doc {
    void* Fn8e26e0(wchar16* s, int n, int flag);                         // 0x008e26e0
    void* Fn8e2c10(wchar16* name, const wchar16** attrs, int n, int f);  // 0x008e2c10
    void  Fn8e2800(void* elem);                                          // 0x008e2800
};
void* __cdecl FUN_0090ac10(void*, void*, int);  // 0x0090ac10
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

    void  Fn8e5600(short* p, int n);                 // 0x008e5600
    int   Fn8e5a20(const char* s, int len, unsigned char fin); // 0x008e5a20
    int   Fn8e5730(void* parser, void* uri);         // 0x008e5730
    void  Fn8e59a0(char param2);                     // 0x008e59a0
    void  Fn8e5ca0();                                // 0x008e5ca0
    void  Fn8e5da0(wchar16* data, int count);        // 0x008e5da0
    void  Fn8e5fb0();                                // 0x008e5fb0
    wchar16* Fn8e5670();                             // 0x008e5670
    void* Fn8e5ea0(void* doc);                       // 0x008e5ea0
    int   Fn8e60a0(void* stream);                    // 0x008e60a0
};
extern "C" void* Fn8e26e0(wchar16* s, int n, int flag);   // 0x008e26e0 (thiscall on Doc)
struct WStr { void push_back(short ch); };   // 0x008e5d10 (thiscall)
// ---- items of slice s008e5320 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" void* Fn8e26e0(wchar16* s, int n, int flag);   // 0x008e26e0 (thiscall on Doc)

// callees this slice defines outside this object (rewrite.py held_callee_protos)
__declspec(noinline) unsigned short Fn8e5580(int entity);  // 0x008e5580 (stays in the slice: not this object's)
void Fn8e5980(void* self, short* p, int n);  // 0x008e5980 (stays in the slice: not this object's)

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
int XmlParser::Fn8e5a20(const char* s, int len, unsigned char fin)
{
    char* c = (char*)this;
    int rc = 0;
    if (XML_Parse(*(void**)(c + 0x220), s, len, fin) == 0) {
        void* doc = *(void**)(c + 4);
        void* uri = *(void**)((char*)doc + 0x48);
        rc = Fn8e5730(*(void**)(c + 0x220), uri);
    }
    *(int*)(c + 0x228) = *(int*)(c + 0x228) + len;
    return rc;
}

// @ 0x008e5a70
bool Fn8e5a70(void* top, void* entity, const char* base, const char* sysid, int ctx)
{
    char* c = *(char**)top;
    char* doc = *(char**)(c + 4);
    if (*(void**)(c + 0x21c) != 0) {
        int n = (int)(*(wchar16**)(c + 0xc) - *(wchar16**)(c + 8));
        if (n != 0) {
            void* r = ((Doc*)doc)->Fn8e26e0(*(wchar16**)(c + 8), n, 1);
            ((Flusher*)*(void**)(c + 0x21c))->Fn8e4350(r);
        }
        if (*(void**)(c + 8) != *(void**)(c + 0xc)) {
            **(wchar16**)(c + 8) = 0;
            *(void**)(c + 0xc) = *(void**)(c + 8);
        }
    }
    if (ctx == 0) {
        *(char*)(c + 0x224) = 0;
        return false;
    }
    int* sink = *(int**)(doc + 0x34);
    if (sink == 0)
        return true;
    void* stream = (*(void* (__thiscall**)(int*, int, void**))(*sink + 0x14))(sink, ctx, &entity);
    if (stream == 0)
        return true;

    char* parser = (char*)FUN_0090ac10(top, entity, 0);
    if (parser == 0)
        return true;

    FUN_00903300(parser, 0, 0);
    FUN_00903320(parser, 0);
    FUN_00903340(parser, 0);
    FUN_00903370(parser, 0, 0);
    FUN_009032e0(parser, c);
    FUN_009033d0(parser, 2);
    int rc = 0;
    if (XML_Parse(parser, (const char*)stream, (int)base, 1) == 0)
        rc = FUN_00903b40(parser);
    XML_ParserFree(parser);
    return rc == 0;
}

// @ 0x008e5b90
void Fn8e5b90(void* parser, const wchar16* name, const wchar16** attrs)
{
    char* c = (char*)parser;
    char* doc = *(char**)(c + 4);
    if (*(void**)(c + 0x21c) != 0) {
        if (*(wchar16**)(c + 0xc) - *(wchar16**)(c + 8) != 0) {
            if (*(wchar16**)(c + 0xc) - *(wchar16**)(c + 8) != 0) {
                void* r = ((Doc*)doc)->Fn8e26e0(*(wchar16**)(c + 8),
                                                 *(wchar16**)(c + 0xc) - *(wchar16**)(c + 8), 1);
                ((Flusher*)*(void**)(c + 0x21c))->Fn8e4350(r);
            }
            if (*(void**)(c + 8) != *(void**)(c + 0xc)) {
                **(wchar16**)(c + 8) = 0;
                *(void**)(c + 0xc) = *(void**)(c + 8);
            }
        }
    }

    int count = 0;
    const wchar16** p = attrs;
    while (*p != 0) { p++; count++; }
    void* elem = ((Doc*)doc)->Fn8e2c10((wchar16*)name, attrs, count / 2, 1);
    if (elem != 0) {
        if (*(int*)(doc + 0x40) == 0)
            ((Doc*)doc)->Fn8e2800(elem);
        else
            ((Flusher*)*(void**)(c + 0x21c))->Fn8e4350(elem);
        *(void**)(c + 0x21c) = elem;
    }
    *(char*)(c + 0x224) = 1;
    XML_DefaultCurrent(*(void**)(c + 0x220));
}

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

// @ 0x008e5e50
void Fn8e5e50(void* parser, int name, unsigned int isparam)
{
    XmlParser* p = (XmlParser*)parser;
    if (isparam == 0) {
        unsigned short e = Fn8e5580(name);
        isparam = e;
        if (e != 0) {
            unsigned int tmp = e;
            p->Fn8e5da0((wchar16*)&tmp, 1);
        }
    }
    XML_DefaultCurrent(*(void**)((char*)p + 0x220));
}

// @ 0x008e5ea0
void* XmlParser::Fn8e5ea0(void* doc)
{
    char* c = (char*)this;
    *(void**)(c + 4) = doc;
    *(void**)c = (void*)0x1437be4;
    void** p = (void**)(c + 0x1c);
    *(void**)(c + 0x18) = p;
    *(void**)(c + 0xc) = p;
    *(void**)(c + 8)  = p;
    *(void**)(c + 0x10) = (void**)((char*)p + 0x200);
    *(wchar16*)p = 0;
    *(void**)(c + 0x21c) = 0;
    *(void**)(c + 0x220) = 0;
    *(char*)(c + 0x224) = 1;
    *(void**)(c + 0x228) = 0;
    *(void**)(c + 0x430) = 0;
    *(void**)(c + 0x434) = 0;
    *(char*)(c + 0x438) = 0;
    *(void**)(c + 0x220) = FUN_0090af20(0);
    FUN_00903300(*(void**)(c + 0x220), (void*)&Fn8e5b90, (void*)&Fn8e5c50);
    FUN_00903320(*(void**)(c + 0x220), (void*)&Fn8e5e20);
    FUN_00903340(*(void**)(c + 0x220), (void*)0x8e5930);
    FUN_00903370(*(void**)(c + 0x220), (void*)0xc2e4e0, (void*)0xc2e4e0);
    FUN_009033b0(*(void**)(c + 0x220), (void*)&Fn8e5a70);
    FUN_00903350(*(void**)(c + 0x220), (void*)&Fn8e5980);
    FUN_009033c0(*(void**)(c + 0x220), (void*)&Fn8e5e50);
    FUN_009032e0(*(void**)(c + 0x220), c);
    FUN_009033d0(*(void**)(c + 0x220), 1);
    *(char*)(c + 0x224) = 1;
    return this;
}

// @ 0x008e5fb0
void XmlParser::Fn8e5fb0()
{
    char* c = (char*)this;
    void* xp = *(void**)(c + 0x220);
    if (xp == 0)
        return;
    int status[2] = { 0, 0 };
    FUN_009035d0(xp, status);
    if (status[0] == 0)
        return;
    FUN_0090a870(xp, 0);
    FUN_00903300(xp, (void*)&Fn8e5b90, (void*)&Fn8e5c50);
    FUN_00903320(xp, (void*)&Fn8e5e20);
    FUN_00903340(xp, (void*)0x8e5930);
    FUN_00903370(xp, (void*)0xc2e4e0, (void*)0xc2e4e0);
    FUN_009033b0(xp, (void*)&Fn8e5a70);
    FUN_00903350(xp, (void*)&Fn8e5980);
    FUN_009033c0(xp, (void*)&Fn8e5e50);
    FUN_009032e0(xp, c);
    FUN_009033d0(xp, 1);
}

// @ 0x008e60a0
int XmlParser::Fn8e60a0(void* stream)
{
    char* c = (char*)this;
    int rc = 0;
    Fn8e5fb0();
    for (;;) {
        char* buf = (char*)FUN_00903400(*(void**)(c + 0x220), 0x1000);
        if (buf == 0)
            break;
        int n = (*(int (__thiscall**)(void*, char*, int))(*(int*)stream + 0x30))(stream, buf, 0x1000);
        if (n == -1)
            break;
        if (FUN_00904580(*(void**)(c + 0x220), n, n != 0x1000) != 1)
            break;
        if (n != 0x1000)
            return rc;
    }
    return Fn8e5730(*(void**)(c + 0x220), *(void**)(*(int*)(c + 4) + 0x48));
}
