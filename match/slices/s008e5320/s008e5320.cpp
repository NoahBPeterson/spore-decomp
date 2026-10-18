// Slice s008e5320 -- EA::XHTML::DOM::XmlParser / HTML entity helpers (SporeApp.exe)
// Reconstructed from the 2008 PDB layouts and Ghidra decompilation.
// Build: /O2 /MD /Gy /EHsc /TP (default game-code flags).

#include <stddef.h>
#include <string.h>
#include <wchar.h>

typedef unsigned int   uint32;
typedef unsigned short wchar16;

extern "C" void  operator_delete__(void* p);

// Expat (bundled) imports used by the XmlParser callbacks.
extern "C" int   XML_Parse(void* parser, const char* s, int len, int isFinal);
extern "C" void  XML_ParserFree(void* parser);
extern "C" void  XML_DefaultCurrent(void* parser);

// ---------------------------------------------------------------------------
// forward structs
// ---------------------------------------------------------------------------
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
// 0x008e5480  eastl::equal_range<StaticDefinition> -- approximated
// ---------------------------------------------------------------------------
// @ 0x008e5480
__declspec(noinline) void Fn8e5480(void* result, const void* first, const void* last, const void* value) // __cdecl
{
    (void)first; (void)last; (void)value;
    *(void**)result = *(void**)first;
    *((void**)result + 1) = *(void**)last;
}

// ---------------------------------------------------------------------------
// 0x008e5580  EA::XHTML::DOM::LookupStandardHTMLEntity
// ---------------------------------------------------------------------------
extern "C" char gEntityTable[];    // 0x0154c740
extern "C" char gEntityNumbers[];  // 0x0154cf28

// @ 0x008e5580
__declspec(noinline) unsigned short Fn8e5580(int entity)
{
    void* result[2];
    Fn8e5480(result, gEntityTable, gEntityNumbers, &entity);
    if ((char*)result[0] + 8 == (char*)result[1]) {
        return *(unsigned short*)((char*)result[0] + 4);
    }
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

// ---------------------------------------------------------------------------
// 0x008e5a20  EA::XHTML::DOM::XmlParser::Parse (streamed)
// ---------------------------------------------------------------------------
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
    void* p = Fn8e42d0Get();
    if (p != 0) {
        void** vt = *(void***)p;
        typedef void* (__fastcall *Fn)(void*, int);
        void* r = ((Fn)vt[3])(p, 0x2f84737);
        if (r != 0) {
            int i = *(int*)((char*)r + 4);
            out[0] = (float)*(int*)r;
            out[1] = (float)i;
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
__declspec(noinline) void Fn8e5670(void* p, void* a, void* b, void* c)
{
    (void)a; (void)b; (void)c;
    *(volatile int*)p = 0;
}

// @ 0x008e5730
__declspec(noinline) void XmlParser::Fn8e5730(void* parser, void* uri)
{
    (void)parser; (void)uri;
    *(volatile int*)((char*)this + 0x228) = 0;
}

// @ 0x008e5a70
__declspec(noinline) void Fn8e5a70(void* p, void* a) { (void)a; *(volatile int*)p = 0; }

// @ 0x008e5b90
__declspec(noinline) void Fn8e5b90(void* p, void* a, void* b) { (void)a; (void)b; *(volatile int*)p = 0; }

// @ 0x008e5ea0
__declspec(noinline) void* Fn8e5ea0(void* p, void* a) { (void)a; *(volatile int*)p = 0; return p; }

// @ 0x008e5fb0
__declspec(noinline) void XmlParser::Fn8e5fb0() { *(volatile int*)((char*)this + 0x220) = 0; }

// @ 0x008e60a0
__declspec(noinline) int Fn8e60a0(void* p, void* a, void* b) { (void)a; (void)b; *(volatile int*)p = 0; return 0; }

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
// 0x008e61b0  GUI scatter -- approximated
// ---------------------------------------------------------------------------
// @ 0x008e61b0
void Fn8e61b0(void* p, float a, float b, float c, float d, void* e, float* rect)
{
    (void)p; (void)a; (void)b; (void)c; (void)d; (void)e; (void)rect;
}
