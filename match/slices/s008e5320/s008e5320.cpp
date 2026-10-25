// Slice s008e5320 -- EA::XHTML::DOM::XmlParser / HTML entity helpers (SporeApp.exe)
// Reconstructed from the 2008 PDB layouts and Ghidra decompilation.
// Build: /O2 /MD /Gy /EHsc /TP (default game-code flags).

#include <stddef.h>
#include <string.h>
#include <wchar.h>

typedef unsigned int   uint32;
typedef unsigned short wchar16;
typedef unsigned char  uint8;

// MSVC's __declspec(noinline) contains a '(' before the function name, which
// upsets the marker/definition scanner; the macro hides it.
#define NOINLINE __declspec(noinline)

extern "C" void  operator_delete__(void* p);

// Expat (bundled) imports used by the XmlParser callbacks.
extern "C" int   XML_Parse(void* parser, const char* s, int len, int isFinal);
extern "C" void  XML_ParserFree(void* parser);
extern "C" void  XML_DefaultCurrent(void* parser);

// Lower-level expat entry points used by the XmlParser (this build keeps the
// per-handler setters as separate functions instead of one XML_Set* wrapper).
extern "C" {
void* FUN_0090af20(int);                        // 0x0090af20  parser create/wrapper
int   FUN_00903b40(void*);                      // 0x00903b40  error code
int   FUN_009035f0(void*);                      // 0x009035f0
int   FUN_00903610(void*);                      // 0x00903610
int   FUN_00903660(void*);                      // 0x00903660
void  FUN_00903300(void*, void*, void*);        // 0x00903300  element handler
void  FUN_00903320(void*, void*);               // 0x00903320  character data handler
void  FUN_00903340(void*, void*);               // 0x00903340
void  FUN_00903350(void*, void*);               // 0x00903350
void  FUN_00903370(void*, void*, void*);        // 0x00903370
void  FUN_009033b0(void*, void*);               // 0x009033b0
void  FUN_009033c0(void*, void*);               // 0x009033c0
void  FUN_009033d0(void*, int);                 // 0x009033d0
void  FUN_009032e0(void*, void*);               // 0x009032e0  user data
void  FUN_009035d0(void*, void*);               // 0x009035d0  get parsing status
void* FUN_00903400(void*, int);                 // 0x00903400  get buffer
int   FUN_00904580(void*, int, int);            // 0x00904580  parse buffer
void  FUN_0090a870(void*, int);                 // 0x0090a870
}
void* __cdecl Fn11e0744(void* dst, const void* src, unsigned n);  // 0x011e0744 (memcpy thunk)

// Expat handlers referenced (not defined) by this slice.
extern "C" void Fn8e5930(void* userData, const wchar16* name);         // 0x008e5930
extern "C" void ReadText_00c2e4e0(void* userData, const wchar16* s);   // 0x00c2e4e0

// ---------------------------------------------------------------------------
// forward structs
// ---------------------------------------------------------------------------
struct Flusher { void Fn8e4350(void* node); };  // 0x008e4350
struct DomNodeIface { virtual void fn0(); };
struct DomNodeBase  { void* Parent(); };   // 0x00ff0420 (thiscall)
// Sink the external-entity handler asks for the entity's bytes.
struct XhtmlEntitySink {
    virtual void  v0();
    virtual void  v1();
    virtual void  v2();
    virtual void  v3();
    virtual void  v4();
    virtual void* OpenStream(int length, int* pLength);   // vtable +0x14
};

struct Doc {
    uint32           pad_0[0x34 / 4];      // +0x00 .. +0x33
    XhtmlEntitySink* mpEntitySink_34;      // +0x34
    uint32           pad_38[2];            // +0x38
    int              mOpenFlags_40;        // +0x40
    void*            mpTagSink_44;         // +0x44
    void*            mpUri_48;             // +0x48

    void* Fn8e26e0(wchar16* s, int n, int flag);                         // 0x008e26e0
    void* Fn8e2c10(wchar16* name, const wchar16** attrs, int n, int f);  // 0x008e2c10
    void  Fn8e2800(void* elem);                                          // 0x008e2800
};
void* __cdecl XML_ExternalEntityParserCreate(void*, void*, int);  // 0x0090ac10

struct XmlParser {
    void*    mpVtbl_0;                 // +0x000
    void*    mpDocument_4;             // +0x004
    wchar16* mpTextBegin_8;            // +0x008  shared string begin
    wchar16* mpTextEnd_c;              // +0x00c
    wchar16* mpTextCapacity_10;        // +0x010  == mpInlinePool (aliased)
    uint32   pad_14;                   // +0x014
    wchar16* mpInlinePool_18;          // +0x018
    wchar16  mInlinePool_1c[0x100];    // +0x01c .. +0x21b (inline buffer)
    void*    mpParserNode_21c;         // +0x21c
    void*    mpXmlParser_220;          // +0x220
    uint8    mbSpace_224;              // +0x224
    uint8    pad_225[3];               // +0x225
    int      mOffset_228;              // +0x228
    wchar16  mBuffer_22c[0x100];       // +0x22c .. +0x42b
    uint32   pad_42c;                  // +0x42c
    int      mCount_430;               // +0x430
    int      mIndex_434;               // +0x434
    uint8    mbFlag_438;               // +0x438

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

// ---------------------------------------------------------------------------
// 0x008e53a0  eastl::lower_bound (8-byte StaticDefinition entries)
// ---------------------------------------------------------------------------
// @ 0x008e53a0
char* Fn8e53a0(char* begin, char* end, const void* key)
{
    int count = (int)(end - begin) >> 3;
    if (count <= 0) return begin;
    const wchar16* k = *(const wchar16**)key;
    do {
        int mid = count >> 1;
        const wchar16* s = *(const wchar16**)(begin + mid * 8);
        wchar16 a = *s;
        const wchar16* kk = k;
        while (a != 0 && a == *kk) {
            s++;
            kk++;
            a = *s;
        }
        if (*s < *kk) {
            begin = begin + 8 + mid * 8;
            mid = count + (-1 - mid);
        }
        count = mid;
    } while (count > 0);
    return begin;
}

// ---------------------------------------------------------------------------
// 0x008e5410  eastl::upper_bound (8-byte StaticDefinition entries)
// ---------------------------------------------------------------------------
// @ 0x008e5410
char* Fn8e5410(char* begin, char* end, const void* key)
{
    int count = (int)(end - begin) >> 3;
    if (count <= 0) return begin;
    const wchar16* k = *(const wchar16**)key;
    do {
        int mid = count >> 1;
        const wchar16* s = *(const wchar16**)(begin + mid * 8);
        wchar16 a = *k;
        const wchar16* kk = k;
        while (a != 0 && a == *s) {
            kk++;
            s++;
            a = *kk;
        }
        if (*s <= *kk) {
            begin = begin + 8 + mid * 8;
            mid = count + (-1 - mid);
        }
        count = mid;
    } while (count > 0);
    return begin;
}

// ---------------------------------------------------------------------------
// 0x008e5480  eastl::equal_range<StaticDefinition> (hidden return slot)
// ---------------------------------------------------------------------------
struct StaticDef { const wchar16* mpName; unsigned short mValue; unsigned short mPad; };
struct StaticRange {
    StaticDef* first;
    StaticDef* second;
    StaticRange() {}
    StaticRange(const StaticRange& o) : first(o.first), second(o.second) {}
};
// @ 0x008e5480
StaticRange Fn8e5480(StaticDef* begin, StaticDef* end, const wchar16** key)
{
    int count = (int)((char*)end - (char*)begin) >> 3;
    if (count > 0) {
        const wchar16* k = *key;
        do {
            int half = count >> 1;
            StaticDef* mid = begin + half;
            const wchar16* nm = mid->mpName;
            const wchar16* p = nm;
            const wchar16* q = k;
            while (*p != 0 && *p == *q) { p++; q++; }
            if (*p < *q) {
                begin = mid + 1;
                count += -1 - half;
            } else {
                const wchar16* p2 = nm;
                const wchar16* q2 = k;
                while (*q2 != 0 && *q2 == *p2) { q2++; p2++; }
                if (*p2 <= *q2) {
                    StaticRange range;
                    range.second = (StaticDef*)Fn8e5410((char*)(mid + 1), (char*)end, key);
                    range.first = (StaticDef*)Fn8e53a0((char*)begin, (char*)mid, key);
                    return range;
                }
                end = mid;
                count = half;
            }
        } while (count > 0);
    }
    StaticRange range;
    range.first = begin;
    range.second = begin;
    return range;
}

// ---------------------------------------------------------------------------
// 0x008e5580  EA::XHTML::DOM::LookupStandardHTMLEntity
// ---------------------------------------------------------------------------
extern "C" char gEntityTable[];    // 0x0154c740
extern "C" char gEntityNumbers[];  // 0x0154cf28

// @ 0x008e5580
NOINLINE unsigned short Fn8e5580(int entity)
{
    const wchar16* key = (const wchar16*)entity;
    StaticRange result = Fn8e5480((StaticDef*)gEntityTable, (StaticDef*)gEntityNumbers, &key);
    if ((char*)result.first + 8 == (char*)result.second)
        return *(unsigned short*)((char*)result.first + 4);
    return 0;
}

// ---------------------------------------------------------------------------
// 0x008e5600  XmlParser::Fn8e5600 -- newline-aware wchar buffer
// ---------------------------------------------------------------------------
// @ 0x008e5600
void XmlParser::Fn8e5600(short* p, int n)
{
    char* c = (char*)this;
    if (n <= 0) return;
    do {
        short s = *p;
        if (s == 10 || s == 0xd) {
            *(char*)(c + 0x438) = 0;
            *(int*)(c + 0x434) = 0;
        } else {
            int idx = *(int*)(c + 0x434);
            *(short*)(c + 0x22c + idx * 2) = s;
            idx = idx + 1;
            *(int*)(c + 0x434) = idx;
            p++;
            if ((unsigned int)idx > 0xff) {
                *(char*)(c + 0x438) = 1;
                *(int*)(c + 0x434) = 0;
            }
        }
        *(int*)(c + 0x430) = *(int*)(c + 0x430) + 1;
        n = n - 1;
    } while (n > 0);
}

// ---------------------------------------------------------------------------
// 0x008e5980  expat character-data sink (cdecl, forwards to Fn8e5600)
// ---------------------------------------------------------------------------
// @ 0x008e5980
void Fn8e5980(void* self, short* p, int n)
{
    ((XmlParser*)self)->Fn8e5600(p, n);
}

// ---------------------------------------------------------------------------
// 0x008e59a0  EA::XHTML::DOM::XmlParser::FlushText
// ---------------------------------------------------------------------------
extern "C" void* Fn8e26e0(wchar16* s, int n, int flag);   // 0x008e26e0 (thiscall on Doc)

// @ 0x008e59a0
NOINLINE void XmlParser::Fn8e59a0(char param2)
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

// ---------------------------------------------------------------------------
// 0x008e5a20  EA::XHTML::DOM::XmlParser::Parse (streamed)
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x008e5c50  EA::XHTML::DOM::XmlParser::EndElementHandler (cdecl callback)
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x008e5ca0  EA::XHTML::DOM::XmlParser::~XmlParser
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x008e5da0  EA::XHTML::DOM::XmlParser::AppendCharacterData
// ---------------------------------------------------------------------------
struct WStr { void push_back(short ch); };   // 0x008e5d10 (thiscall)

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

// ---------------------------------------------------------------------------
// 0x008e5e20  CharacterDataHandler (cdecl callback)
// ---------------------------------------------------------------------------
// @ 0x008e5e20
void Fn8e5e20(void* parser, wchar16* data, int count)
{
    XmlParser* p = (XmlParser*)parser;
    p->Fn8e5da0(data, count);
    XML_DefaultCurrent(*(void**)((char*)p + 0x220));
}

// ---------------------------------------------------------------------------
// 0x008e5e50  SkippedEntityHandler (cdecl callback)
// ---------------------------------------------------------------------------
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

// ---------------------------------------------------------------------------
// 0x008e5320  GUI metric reader (stdcall, 1 arg)
// ---------------------------------------------------------------------------
extern "C" void* Fn8e42d0Get();   // 0x008e42d0 (ecx-inherited singleton)

// @ 0x008e5320
char __stdcall Fn8e5320(float* out)
{
    out[1] = 16.0f;
    out[0] = 16.0f;
    int* p = (int*)Fn8e42d0Get();
    if (p != 0) {
        int* r = (int*)(*(int* (__thiscall**)(int*, int))(*(int*)p + 0xc))(p, 0x2f84737);
        if (r != 0) {
            float tmp[2];
            tmp[0] = (float)r[0];
            tmp[1] = (float)r[1];
            out[0] = tmp[0];
            out[1] = tmp[1];
        }
    }
    return 1;
}

// ===========================================================================
// Approximated / stubbed functions (large reconstruction not attempted)
// ===========================================================================

// @ 0x008e5370
struct GuiThing {
    void Fn8e4400(int a, int b, int c);   // thiscall
    __declspec(noinline) void* Fn8e5370(int a, int b, int c);
};
void* GuiThing::Fn8e5370(int a, int b, int c)
{
    Fn8e4400(a, b, c);
    *(void**)this = (void*)0x1436da8;
    return this;
}

// @ 0x008e55d0
struct GuiThing2 {
    void Fn8e52b0(int a, int n);          // thiscall
    __declspec(noinline) void* Fn8e55d0(int a, int b, int c);
};
void* GuiThing2::Fn8e55d0(int a, int b, int c)
{
    Fn8e52b0(a, 2);
    *(void**)this = (void*)0x1437bd8;
    *(int*)((char*)this + 0x18) = b;
    *(int*)((char*)this + 0x1c) = c;
    return this;
}

// @ 0x008e5670
NOINLINE wchar16* XmlParser::Fn8e5670()
{
    if (mbFlag_438 != 0) {
        int idx = mIndex_434 - 0x40;
        if (idx >= 0) {
            Fn11e0744(mBuffer_22c, mBuffer_22c + idx, 0x80);
        } else {
            Fn11e0744(mBuffer_22c - idx, mBuffer_22c, idx * 2 + 0x80);
            Fn11e0744(mBuffer_22c, (wchar16*)((char*)mBuffer_22c + idx * 2 + 0x200), idx * -2);
        }
        mIndex_434 = 0x40;
    } else if ((unsigned int)mIndex_434 > 0x40) {
        Fn11e0744(mBuffer_22c, (wchar16*)((char*)mBuffer_22c + mIndex_434 * 2 - 0x80), 0x80);
        mIndex_434 = 0x40;
    }
    mBuffer_22c[mIndex_434] = 0;
    return mBuffer_22c;
}

// ---------------------------------------------------------------------------
// 0x008e5730  expat element/entity name sink (thiscall, 2 args, ret 8)
// ---------------------------------------------------------------------------
struct AttrSrc;

// @ 0x008e5730
int XmlParser::Fn8e5730(void* parser, void* uri)
{
    char* c = (char*)this;
    int tag;
    switch (FUN_00903b40(parser)) {
    case 1:  tag = 0x2320000; break;
    case 3:  tag = 0x2320002; break;
    case 4:  tag = 0x2320003; break;
    case 5:  tag = 0x2320004; break;
    case 6:  tag = 0x2320005; break;
    case 7:  tag = 0x2320006; break;
    case 8:  tag = 0x2320007; break;
    case 9:  tag = 0x2320008; break;
    case 10: tag = 0x2320009; break;
    case 11: tag = 0x232000a; break;
    case 12: tag = 0x232000b; break;
    case 13: tag = 0x232000c; break;
    case 14: tag = 0x232000d; break;
    case 15: tag = 0x232000e; break;
    case 16: tag = 0x232000f; break;
    case 17: tag = 0x2320010; break;
    case 18: tag = 0x2320011; break;
    case 19: tag = 0x2320012; break;
    case 20: tag = 0x2320013; break;
    case 22: tag = 0x2320014; break;
    case 24: tag = 0x2320015; break;
    case 27: tag = 0x2320016; break;
    case 28: tag = 0x2320016; break;
    case 29: tag = 0x2320017; break;
    case 30: tag = 0x2320018; break;
    case 31: tag = 0x2320019; break;
    case 32: tag = 0x232001a; break;
    default: tag = 0x2320001; break;
    }
    int* sink = *(int**)(*(int*)(c + 4) + 0x44);
    if (sink != 0) {
        int n = FUN_009035f0(*(void**)(c + 0x220));
        if (n > 0) {
            int a = FUN_00903610(parser);
            int b = FUN_00903660(parser);
            int edx = *sink;
            wchar16* nm = Fn8e5670();
            (*(void (__thiscall**)(int*, int, void*, int, int, wchar16*))(edx + 4))(sink, tag, uri, a, b, nm);
            return tag;
        }
        (*(void (__thiscall**)(int*, int, void*, int, int, int))(*sink + 4))(sink, tag, uri, 0, 0, 0);
    }
    return tag;
}

// ---------------------------------------------------------------------------
// 0x008e5a70  ExternalEntityRefHandler (cdecl callback)
// ---------------------------------------------------------------------------
// @ 0x008e5a70
int Fn8e5a70(void** top, void* entity, int base, int sysid, int length)
{
    XmlParser* p = (XmlParser*)*top;
    Doc* doc = (Doc*)p->mpDocument_4;
    if (p->mpParserNode_21c != 0) {
        if ((int)(p->mpTextEnd_c - p->mpTextBegin_8) != 0) {
            if ((int)(p->mpTextEnd_c - p->mpTextBegin_8) != 0) {
                void* r = doc->Fn8e26e0(p->mpTextBegin_8,
                                        (int)(p->mpTextEnd_c - p->mpTextBegin_8), 1);
                ((Flusher*)p->mpParserNode_21c)->Fn8e4350(r);
            }
            if (p->mpTextBegin_8 != p->mpTextEnd_c) {
                *p->mpTextBegin_8 = 0;
                p->mpTextEnd_c = p->mpTextBegin_8;
            }
        }
    }
    if (length == 0) {
        p->mbSpace_224 = 0;
        return false;
    }
    XhtmlEntitySink* sink = *(XhtmlEntitySink**)((char*)doc + 0x34);
    if (sink == 0)
        return true;
    void* stream = sink->OpenStream(length, &length);
    if (stream == 0)
        return true;

    int rc = 0;
    void* parser = XML_ExternalEntityParserCreate(top, entity, 0);   // 0x0090ac10
    if (parser != 0) {
        FUN_00903300(parser, 0, 0);
        FUN_00903320(parser, 0);
        FUN_00903340(parser, 0);
        FUN_00903370(parser, 0, 0);
        FUN_009032e0(parser, p);
        FUN_009033d0(parser, 2);
        if (XML_Parse(parser, (const char*)stream, length, 1) == 0)
            rc = FUN_00903b40(parser);
        XML_ParserFree(parser);
    }
    return rc == 0;
}

// ---------------------------------------------------------------------------
// 0x008e5b90  ElementHandler (cdecl callback)
// ---------------------------------------------------------------------------
// @ 0x008e5b90
void Fn8e5b90(void* parser, const wchar16* name, const wchar16** attrs)
{
    XmlParser* p = (XmlParser*)parser;
    Doc* doc = (Doc*)p->mpDocument_4;
    if (p->mpParserNode_21c != 0) {
        if ((int)(p->mpTextEnd_c - p->mpTextBegin_8) != 0) {
            if ((int)(p->mpTextEnd_c - p->mpTextBegin_8) != 0) {
                void* r = doc->Fn8e26e0(p->mpTextBegin_8,
                                        (int)(p->mpTextEnd_c - p->mpTextBegin_8), 1);
                ((Flusher*)p->mpParserNode_21c)->Fn8e4350(r);
            }
            if (p->mpTextBegin_8 != p->mpTextEnd_c) {
                *p->mpTextBegin_8 = 0;
                p->mpTextEnd_c = p->mpTextBegin_8;
            }
        }
    }

    int count = 0;
    const wchar16** ppAttr = attrs;
    while (*ppAttr != 0) {
        ppAttr++;
        count++;
    }
    void* elem = doc->Fn8e2c10((wchar16*)name, attrs, count / 2, 1);
    if (elem != 0) {
        if (doc->mOpenFlags_40 == 0)
            doc->Fn8e2800(elem);
        else
            ((Flusher*)p->mpParserNode_21c)->Fn8e4350(elem);
        p->mpParserNode_21c = elem;
    }
    p->mbSpace_224 = 1;
    XML_DefaultCurrent(p->mpXmlParser_220);
}

// ---------------------------------------------------------------------------
// 0x008e5ea0  XmlParser::XmlParser(document)  (thiscall, ret 4)
// ---------------------------------------------------------------------------
// @ 0x008e5ea0
void* XmlParser::Fn8e5ea0(void* doc)
{
    char* c = (char*)this;
    mpDocument_4 = doc;
    wchar16* p = mInlinePool_1c;
    mpVtbl_0 = (void*)0x1437be4;
    mpInlinePool_18 = p;
    mpTextEnd_c = p;
    mpTextBegin_8 = p;
    mpTextCapacity_10 = p + 0x100;
    *p = 0;
    mpParserNode_21c = 0;
    mpXmlParser_220 = 0;
    mbSpace_224 = 1;
    mOffset_228 = 0;
    mCount_430 = 0;
    mIndex_434 = 0;
    mbFlag_438 = 0;
    mpXmlParser_220 = FUN_0090af20(0);
    FUN_00903300(mpXmlParser_220, (void*)&Fn8e5b90, (void*)&Fn8e5c50);
    FUN_00903320(mpXmlParser_220, (void*)&Fn8e5e20);
    FUN_00903340(mpXmlParser_220, (void*)0x8e5930);
    FUN_00903370(mpXmlParser_220, (void*)0xc2e4e0, (void*)0xc2e4e0);
    FUN_009033b0(mpXmlParser_220, (void*)&Fn8e5a70);
    FUN_00903350(mpXmlParser_220, (void*)&Fn8e5980);
    FUN_009033c0(mpXmlParser_220, (void*)&Fn8e5e50);
    FUN_009032e0(mpXmlParser_220, this);
    FUN_009033d0(mpXmlParser_220, 1);
    mbSpace_224 = 1;
    return this;
}

// ---------------------------------------------------------------------------
// 0x008e5fb0  XmlParser::Fn8e5fb0 -- re-init expat handlers
// ---------------------------------------------------------------------------
// @ 0x008e5fb0
void XmlParser::Fn8e5fb0()
{
    if (mpXmlParser_220 == 0)
        return;
    int status[2];
    FUN_009035d0(mpXmlParser_220, status);
    if (status[0] == 0)
        return;
    FUN_0090a870(mpXmlParser_220, 0);
    FUN_00903300(mpXmlParser_220, (void*)&Fn8e5b90, (void*)&Fn8e5c50);
    FUN_00903320(mpXmlParser_220, (void*)&Fn8e5e20);
    FUN_00903340(mpXmlParser_220, (void*)0x8e5930);
    FUN_00903370(mpXmlParser_220, (void*)0xc2e4e0, (void*)0xc2e4e0);
    FUN_009033b0(mpXmlParser_220, (void*)&Fn8e5a70);
    FUN_00903350(mpXmlParser_220, (void*)&Fn8e5980);
    FUN_009033c0(mpXmlParser_220, (void*)&Fn8e5e50);
    FUN_009032e0(mpXmlParser_220, this);
    FUN_009033d0(mpXmlParser_220, 1);
}

// ---------------------------------------------------------------------------
// 0x008e60a0  XmlParser::Parse(stream) (thiscall, ret 4)
// ---------------------------------------------------------------------------
// @ 0x008e60a0
int XmlParser::Fn8e60a0(void* stream)
{
    int rc = 0;
    Fn8e5fb0();
    for (;;) {
        char* buf = (char*)FUN_00903400(mpXmlParser_220, 0x1000);
        bool bBuffer = buf != 0;
        if (bBuffer) {
            int n = (*(int (__thiscall**)(void*, char*, int))(*(int*)stream + 0x30))(stream, buf, 0x1000);
            int bFinal = n != 0x1000;
            if (n == -1)
                break;
            if (FUN_00904580(mpXmlParser_220, n, bFinal) != 1)
                break;
            if (bFinal)
                return rc;
        } else {
            break;
        }
    }
    return Fn8e5730(mpXmlParser_220, ((Doc*)mpDocument_4)->mpUri_48);
}

// ---------------------------------------------------------------------------
// 0x008e6130  ctor
// ---------------------------------------------------------------------------
// @ 0x008e6130
struct GuiThing3 {
    __declspec(noinline) void* Fn8e6130(void* a);
};
void* GuiThing3::Fn8e6130(void* a)
{
    char* c = (char*)this;
    *(int*)(c + 4) = 0;
    *(int*)(c + 8) = 0;
    *(void**)c = (void*)0x1437bf4;
    *(void**)(c + 0xc) = a;
    *(int*)(c + 0x10) = -1;
    *(int*)(c + 0x14) = 0;
    *(int*)(c + 0x18) = 3;
    *(int*)(c + 0x1c) = 0;
    *(float*)(c + 0x20) = 0.0f;
    *(int*)(c + 0x24) = 0;
    *(float*)(c + 0x28) = 0.0f;
    *(int*)(c + 0x2c) = 0;
    *(char*)(c + 0x44) = 0;
    return this;
}

// ---------------------------------------------------------------------------
// 0x008e6180  helper
// ---------------------------------------------------------------------------
struct SubA { void* Fn8ec910(); };
struct SubB { void Fn8eb910(void* a, void* arg); };
struct Q18 { __declspec(noinline) void Fn8e6180(void* arg); };

// @ 0x008e6180
void Q18::Fn8e6180(void* arg)
{
    char* c = (char*)this;
    if (*(int*)(c + 0x10) == -1) {
        void* s = ((SubA*)*(void**)(c + 0xc))->Fn8ec910();
        *(void**)(c + 0x10) = s;
    }
    ((SubB*)*(void**)(c + 0xc))->Fn8eb910(*(void**)(c + 0x10), arg);
}

// ---------------------------------------------------------------------------
// 0x008e61b0  GUI rect scatter (cdecl; 16-byte RectF passed by value)
// ---------------------------------------------------------------------------
struct RectF {
    float x0, y0, x1, y1;
    bool Intersect(const RectF& a, const RectF& b);  // 0x00634b60
};

// @ 0x008e61b0
void Fn8e61b0(void** pp, RectF r, void* p6, RectF* p7)
{
    if (p7->x0 <= r.x0 && r.x1 <= p7->x1 && p7->y0 <= r.y0 && r.y1 <= p7->y1) {
        RectF out;
        out.x0 = 0.0f;
        out.y0 = 0.0f;
        out.x1 = 1.0f;
        out.y1 = 1.0f;
        (*(void (__thiscall**)(void*, const RectF*, void*, RectF*))
             ((*(int*)*pp) + 0x58))(*pp, &r, p6, &out);
        return;
    }
    float w = r.x1 - r.x0;
    float h = r.y1 - r.y0;
    if (w >= 1.0f && h >= 1.0f) {
        RectF inter = r;
        inter.Intersect(r, *p7);
        if (inter.x0 != inter.x1 && inter.y0 != inter.y1) {
            float u = 1.0f / w;
            float v = 1.0f / h;
            RectF out;
            out.x0 = (inter.x0 - r.x0) * u;
            out.y0 = (inter.y0 - r.y0) * v;
            out.x1 = (inter.x1 - r.x0) * u;
            out.y1 = (inter.y1 - r.y0) * v;
            (*(void (__thiscall**)(void*, const RectF*, void*, RectF*))
                 ((*(int*)*pp) + 0x58))(*pp, &inter, p6, &out);
        }
    }
}
