// Slice s008e2dd0 -- EA::XHTML DOM / CSS parser helpers (SporeApp.exe)
// Reconstructed from the 2008 PDB layouts and Ghidra decompilation.
// Build: /O2 /MD /Gy /EHsc /TP (default game-code flags).

#include <stddef.h>
#include <string.h>
#include <wchar.h>
#include <wctype.h>

typedef unsigned int   uint32;
typedef unsigned short wchar16;

extern "C" void operator_delete__(void* p);

// ---------------------------------------------------------------------------
// Small internal helper used by the CSSParser destructor (inlined in original)
// ---------------------------------------------------------------------------
static void FreeWCStr(char* begin, char* capacity)
{
    if (((capacity - begin) & ~1) > 2 && begin) {
        operator_delete__(begin);
    }
}

// ===========================================================================
// 0x008e2ed0  EA::XHTML::Style::CSSParser::~CSSParser
// ===========================================================================
// @ 0x008e2ed0
void __fastcall Fn8e2ed0(void* pThis)
{
    char* c = (char*)pThis;
    FreeWCStr(*(char**)(c + 0x50), *(char**)(c + 0x58));
    FreeWCStr(*(char**)(c + 0x38), *(char**)(c + 0x40));
    FreeWCStr(*(char**)(c + 0x14), *(char**)(c + 0x1c));
}

// ===========================================================================
// 0x008e2dd0  CSSParser constructor (approximated)
// ===========================================================================
extern "C" int  Fn8e25d0(void* p, int n);          // 0x008e25d0
extern char*    GetXHTMLResourceProvider();        // EA::XHTML::Resource::GetResourceProvider

struct StackAllocator {
    void* ctor(void* a, uint32 b, void* c, void* d, void* e);   // 0x00928cd0
    void  Init(void* a, uint32 b, void* c, void* d, void* e);   // 0x00928b00
};

// @ 0x008e2dd0
void* __fastcall Fn8e2dd0(int* pThis, int param_2)
{
    void** p = (void**)pThis;
    p[0] = (void*)0x01436d94;                 // CSSParser vtable (AddRef form)
    p[1] = 0;                                 // reference count
    p[0] = (void*)0x01436ddc;                 // CSSParser vtable (final)
    StackAllocator* pool = (StackAllocator*)(p + 2);
    pool->ctor(0, 0xffffffffu, 0, 0, 0);
    ((unsigned char*)p)[0x2c] = 0;
    p[0xc] = 0;
    p[0xd] = GetXHTMLResourceProvider();
    p[0xe] = 0;
    p[0xf] = 0;
    p[0x10] = 0;
    p[0x11] = 0;
    p[0x12] = 0;
    p[0x13] = 0;

    p[0x14] = p + 0x1a;                       // string free-list heads
    p[0x15] = p + 0x1a;
    p[0x18] = p + 0x1a;
    p[0x16] = p + 0x2a;

    p[0x2a] = p + 0x30;
    p[0x2b] = p + 0x30;
    p[0x2e] = p + 0x30;
    p[0x2c] = p + 0x40;

    p[0x40] = p + 0x40;
    p[0x41] = p + 0x40;

    p[0x42] = p + 0x48;
    p[0x43] = p + 0x48;
    p[0x46] = p + 0x48;
    p[0x44] = p + 199;

    pool->Init(0, 0, 0, 0, 0);
    if (param_2 != 0)
        p[0x12] = (void*)Fn8e25d0((void*)param_2, -1);
    return p;
}

// ===========================================================================
// 0x008e2f30  vector<bool,...> insert helper (EASTL) -- approximated
// ===========================================================================
extern "C" void Fn829110(void*, void*, void*, void*, void*);   // 0x00829110
extern "C" void Fnac97a0(void*, void*, void*);                 // 0x00ac97a0
extern "C" void* operator_new(int);                            // CRT new (0x00f473a0)
extern "C" void  Fn6782c0(void*, void*, void*);                // 0x006782c0 copy_impl::do_copy
extern "C" void* memcpy(void*, const void*, unsigned int);     // 0x011e0744

// @ 0x008e2f30
void Fn8e2f30(int* pThis, char* first, char* last, char* pos)
{
    if (last == pos)
        return;
    int*  end = (int*)pThis[1];
    uint32 n  = (uint32)((pos - last) >> 2);

    if (n <= (uint32)(((char*)pThis[2] - (char*)end) >> 2)) {
        // enough spare capacity
        uint32 off = (uint32)(((char*)end - first) >> 2);
        if (off <= n) {
            char* mid = last + off * 4;
            Fn829110(0, mid, pos, (void*)end, last);
            pThis[1] = (int)((char*)pThis[1] + (n - off) * 4);
            Fn829110(0, first, (void*)end, (void*)pThis[1], last);
            pThis[1] = (int)((char*)pThis[1] + off * 4);
            Fnac97a0(last, mid, first + off * 4);
            return;
        }
        uint32 offBytes = n * 4;
        char*  split    = (char*)end - offBytes;
        Fn829110(0, split, (void*)end, (void*)end, last);
        pThis[1] = (int)((char*)pThis[1] + offBytes);
        Fnac97a0(first, split, (void*)end);
        Fn6782c0(last, pos, first);
        return;
    }

    // grow: newCap = max(used*2 (or 1), used+n)
    uint32 used   = (uint32)(((char*)end - (char*)pThis[0]) >> 2);
    uint32 newCap = used * 2;
    if (used == 0)
        newCap = 1;
    uint32 want = n + used;
    if (want < newCap)
        want = newCap;

    int* nb = (want == 0) ? 0 : (int*)operator_new((int)want * 4);
    uint32 headBytes = (uint32)(first - (char*)pThis[0]);
    char*  headEnd   = (char*)nb + (headBytes >> 2) * 4;
    if (headBytes != 0)
        memcpy(nb, (void*)pThis[0], headBytes);
    Fn829110(0, last, pos, headEnd, last);          // insert [last,pos)
    uint32 tailBytes = (uint32)((char*)pThis[1] - first);
    char*  tailStart = headEnd + (n * 4);
    if (tailBytes != 0)
        memcpy(tailStart, first, tailBytes);

    int* old = (int*)pThis[0];
    if (old != 0 && old != (int*)pThis[4])
        operator_delete__(old);
    pThis[1] = (int)(tailStart + (tailBytes >> 2) * 4);
    pThis[0] = (int)nb;
    pThis[2] = (int)((char*)nb + want * 4);
}

// ===========================================================================
// 0x008e3380  Document::FetchResources (recursive)
// @ 0x008e3600  Document::Fn8e3600
// ===========================================================================
extern "C" const wchar16 STR_href_13f36b0[];         // 0x013f36b0  L"href"
extern "C" const wchar16 STR_rel_13f36a8[];          // 0x013f36a8  L"rel"
extern "C" const wchar16 STR_type_13f36bc[];         // 0x013f36bc  L"type"
extern "C" const wchar16 STR_textcss_1436e68[];      // 0x01436e68  L"text/css"
extern "C" const wchar16 STR_stylesheet_1436e34[];   // 0x01436e34  L"stylesheet"
extern "C" const wchar16 STR_src_1436bf8[];          // 0x01436bf8  L"src"
extern "C" const char   STR_ssfactory_1436e4c[];     // 0x01436e4c  "XHTML/Page/Style/Stylesheet"
extern "C" wchar16      gEmptyString16_1667bac[];    // 0x01667bac  eastl::gEmptyString16

int  __fastcall Fn8e42c0(void* p);                                  // 0x008e42c0 (defined below)
void __fastcall Fn8e3100(void* pThis, int url, void* a, void* b, char c, int d);  // 0x008e3100
struct StylesheetQueue;                                             // defined below

// EA::XHTML::DOM::Node pending-stylesheet queue (thiscall members)
struct StylesheetQueueFwd {
    void Fn8e42e0(void* arg);       // @ 0x008e42e0
};
extern "C" int   Fn8e2580(void* elem, const wchar16* attr, const wchar16* val); // 0x008e2580 attr match (reg ABI)
extern "C" void* Fn8f3900(void* self, int a, wchar16* s);           // 0x008f3900
extern "C" void* Fn8f9db0(wchar16* base);                           // 0x008f9db0 Stylesheet::Stylesheet
extern "C" char  Fn8f9220(void* parser, void* stylesheet);          // 0x008f9220 CSSParser::Parse
extern "C" void* FnF473a0_new(int size, const char* file, int a, int b, int c, int d);  // 0x00f473a0

// EA::XHTML::DOM::Element (only the members this path touches)
struct FetchElem {
    virtual void* v0();
    virtual void* v1();
    virtual void* GetText(void* str);                 // vtable slot 2 (+0x08)
    char      _pad04[0x28 - 0x04];
    int       mElementType;                           // +0x28
    int       mResourceIndex;                         // +0x2c
    wchar16*  GetAttrValue(const wchar16* attr);      // 0x008e45b0
    int       Type();                                 // 0x00fc7e50
};

// Stack-resident CSSParser (see 0x008e2dd0 for the full layout)
struct CSSParserLocal {
    char  _pad00[0x04];
    void* mpErrorListener;                            // +0x04
    char  _pad08[0x68 - 0x08];
};

struct Doc {
    char      _pad00[0x48];
    wchar16*  mpBaseURI;        // +0x48
    wchar16*  mpDocumentURI;    // +0x4c
    char      _pad50[0x118 - 0x50];
    void*     mpErrorListener;  // +0x118
    void Fn8e3380(void* elem, void* arg);   // @ 0x008e3380
    void Fn8e3600(void* arg);               // @ 0x008e3600
};

// @ 0x008e3380
__declspec(noinline) void Doc::Fn8e3380(void* elem, void* arg)
{
    FetchElem* e = (FetchElem*)elem;

    if (e->mElementType == 6) {                       // Element_Base
        wchar16* href = e->GetAttrValue(STR_href_13f36b0);
        if (href != 0)
            this->mpBaseURI = href;
        return;
    }

    if (e->mElementType == 7) {                       // Element_Style
        if (Fn8e42c0(e) != 0)
            return;
        wchar16* type = e->GetAttrValue(STR_type_13f36bc);
        if (type != STR_textcss_1436e68 &&
            (type == 0 || _wcsicmp((const wchar_t*)type, (const wchar_t*)STR_textcss_1436e68) != 0))
            return;

        wchar16* str[3];
        str[0] = gEmptyString16_1667bac;
        str[1] = gEmptyString16_1667bac;
        str[2] = gEmptyString16_1667bac + 1;
        e->GetText(str);                              // vtable slot 2 fills the string

        void* blob = FnF473a0_new(0x70, STR_ssfactory_1436e4c, 0, 0, 0, 0);
        void* sheet = 0;
        if (blob != 0) {
            wchar16* base = this->mpBaseURI;
            if (base == 0)
                base = this->mpDocumentURI;
            sheet = Fn8f9db0(base);
        }
        Fn8f3900((char*)sheet + 8, (int)(size_t)this, str[0]);

        CSSParserLocal parser;
        parser.mpErrorListener = this->mpErrorListener;
        char parsed = Fn8f9220(&parser, sheet);
        if (parsed == 0) {
            if (sheet != 0)
                (*(void(__fastcall**)(int))(*(int*)sheet + 8))(1);
            sheet = 0;
        }
        ((StylesheetQueueFwd*)e)->Fn8e42e0(0);            // (thiscall on the element)
        Fn8e2ed0(&parser);

        if (str[0] != gEmptyString16_1667bac && str[0] != 0)
            operator_delete__(str[0]);
        return;
    }

    if (e->mElementType == 8) {                       // Element_Link
        wchar16* href = e->GetAttrValue(STR_href_13f36b0);
        if (Fn8e42c0(e) != 0)
            return;
        int ok = Fn8e2580(e, STR_rel_13f36a8, (wchar16*)STR_stylesheet_1436e34);
        if (ok == 0 &&
            Fn8e2580(e, STR_type_13f36bc, (wchar16*)STR_textcss_1436e68) == 0)
            return;
        ((StylesheetQueueFwd*)e)->Fn8e42e0(0);
        if (href == 0)
            return;
        Fn8e3100(this, (int)(size_t)href, 0, (void*)(size_t)e->mResourceIndex, 1, (int)(size_t)arg);
        return;
    }

    if (e->mElementType == 9) {                       // Element_Image
        wchar16* src = e->GetAttrValue(STR_src_1436bf8);
        if (Fn8e42c0(e) != 0)
            return;
        ((StylesheetQueueFwd*)e)->Fn8e42e0(0);
        if (src == 0)
            return;
        Fn8e3100(this, (int)(size_t)src, (void*)1, (void*)(size_t)e->mResourceIndex, 0, (int)(size_t)arg);
        return;
    }

    // generic element: recurse into the sibling chain of the child list
    void* anchorLink = *(void**)((char*)e + 0x18);
    void* stop       = (char*)e + 0x14;
    FetchElem* child = anchorLink != 0 ? (FetchElem*)((char*)anchorLink - 4) : 0;
    for (;;) {
        if (child == stop)
            break;
        if (child->Type() == 1)
            this->Fn8e3380(child, arg);
        void* next = *(void**)((char*)child + 4);
        child = next != 0 ? (FetchElem*)((char*)next - 4) : 0;
    }
}

// @ 0x008e3600
void Doc::Fn8e3600(void* arg)
{
    void* q = *(void**)((char*)this + 0x40);
    if (q) Fn8e3380(q, arg);
}

// ===========================================================================
// 0x008e3850  vector<AutoRefCount<Document>>::push_back -- returns index
// ===========================================================================
// 0x00962210  vector grow/insert helper; ecx = the vector object itself
struct DocumentVec {
    void Fn962210(void* end, void** out);
};
extern void* Fn8e28b0Thunk();

// @ 0x008e3850
__declspec(noinline) int __fastcall Fn8e3850(void* pThis)
{
    char* base = (char*)pThis + 0x108;
    int* end = *(int**)(base + 4);
    int  idx = (int)(((char*)end - *(char**)base) >> 2);
    int* local = 0;
    if ((char*)end < *(char**)(base + 8)) {
        *(int**)(base + 4) = end + 1;
        if (end) { *end = 0; return idx; }
    } else {
        ((DocumentVec*)base)->Fn962210(end, (void**)&local);
        if (local) {
            void** vt = *(void***)local;
            typedef void (__fastcall *Fn)(void*);
            ((Fn)vt[1])(local);
        }
    }
    return idx;
}

// ===========================================================================
// 0x008e38b0  scan URI scheme
// ===========================================================================
// @ 0x008e38b0
unsigned int Fn8e38b0(wchar16* p)
{
    while (iswctype(*p, 0x107) || *p == 0x2b || *p == 0x2e || *p == 0x2d) {
        ++p;
    }
    return (unsigned int)(((*p != 0x3a) - 1) & (unsigned int)(size_t)p);
}

// ===========================================================================
// 0x008e3900  scan URI authority/host
// ===========================================================================
// @ 0x008e3900
wchar16* Fn8e3900(wchar16* p)
{
    int ok = iswctype(*p, 0x157);
    while (ok && *p != 0x2f && *p != 0x3b && *p != 0x3f && *p != 0x23) {
        ++p;
        ok = iswctype(*p, 0x157);
    }
    return p;
}

// ===========================================================================
// 0x008e3960  scan URI path
// ===========================================================================
// @ 0x008e3960
wchar16* Fn8e3960(wchar16* p)
{
    int ok = iswctype(*p, 0x157);
    while (ok && *p != 0x3b && *p != 0x3f && *p != 0x23) {
        ++p;
        ok = iswctype(*p, 0x157);
    }
    return p;
}

// ===========================================================================
// 0x008e3a10  trim last path element (uses EBX for the string object) - approx
// ===========================================================================
// @ 0x008e3a10
char Fn8e3a10(int* strObj, int idx)
{
    wchar16* begin = (wchar16*)strObj[0];
    wchar16* end   = (wchar16*)strObj[1];
    wchar16* limit = begin + idx;
    if (end == limit) return 0;
    wchar16* p = end;
    for (;;) {
        p -= 1;
        if (p <= limit) break;
        if (*(p - 1) == 0x2f) break;          // step back over a path separator
    }
    if (p != end) {
        memmove(p, end, 2);
        strObj[1] = (int)((char*)strObj[1] - ((char*)end - (char*)p));
    }
    return 1;
}

// ===========================================================================
// 0x008e3a70  basic_string::erase(pos, count)
// ===========================================================================
struct WStrErase { int* Fn8e3a70(uint32 pos, uint32 count); };   // 0x008e3a70 (thiscall)

// @ 0x008e3a70
int* WStrErase::Fn8e3a70(uint32 pos, uint32 count)
{
    int* pThis = (int*)this;
    char* begin = (char*)pThis[0];
    char* end   = (char*)pThis[1];
    uint32 avail = (uint32)((end - begin) >> 1) - pos;
    uint32 n = (count <= avail) ? count : avail;
    char* src = begin + (n + pos) * 2;
    char* dst = begin + pos * 2;
    if (dst != src) {
        memmove(dst, src, ((end - src) >> 1) * 2 + 2);
        pThis[1] = (int)(pThis[1] + (((src - dst) >> 1) * -2));
    }
    return (int*)this;
}

// ===========================================================================
// 0x008e3b90  ConvertURLToFilePath
// ===========================================================================
extern "C" int   Fn920f00(void*);                  // 0x00920f00
extern "C" const wchar16 STR_file_1436e9c[];       // 0x01436e9c  L"file:"
extern "C" const wchar16 STR_localhost_1436e88[];  // 0x01436e88  L"localhost"
extern "C" const wchar16 STR_root_13fa030[];       // 0x013fa030  L"/"

// eastl::basic_string<wchar16, fixed_vector_allocator<...>>
struct WStr {
    wchar16* mpBegin;    // +0x00
    wchar16* mpEnd;      // +0x04
    void* assign(wchar16* first, wchar16* last);    // 0x00678ee0
    void* append(wchar16* first, wchar16* last);    // 0x00672750
    void* assignCStr(const wchar16* s);             // 0x00678ff0
    int   find(int ch, int from);                   // 0x008364c0
    void* appendCStr(const wchar16* s);             // 0x005d6fc0
    void* appendChar(wchar16 ch);                   // 0x008e3f10
};

// @ 0x008e3b90
uint32 Fn8e3b90(wchar16* url, int* outStr)
{
    WStr* out = (WStr*)outStr;
    if (url == 0)
        return 0;

    wchar16* scheme = (wchar16*)(size_t)Fn8e38b0(url);
    if (scheme != 0) {
        if (_wcsnicmp((const wchar_t*)url, (const wchar_t*)STR_file_1436e9c, 5) != 0)
            return 0;
        url = scheme + 1;
    }

    if (url[0] == 0x2f && url[1] == 0x2f) {
        wchar16* host = url + 2;
        wchar16* hostEnd = Fn8e3900(host);
        uint32 n = (uint32)(hostEnd - host);
        if (n != 0 && (n != 9 || _wcsnicmp((const wchar_t*)host,
                                           (const wchar_t*)STR_localhost_1436e88, 9) != 0))
            return 0;
        url = hostEnd;
    }

    wchar16* seg = url;
    wchar16* segEnd = Fn8e3960(url);
    if (seg[0] == 0x2f) {
        wchar16* rootEnd = (wchar16*)STR_root_13fa030;
        while (*rootEnd)
            ++rootEnd;
        out->assign((wchar16*)STR_root_13fa030, rootEnd);
        seg += 1;
    } else if (out->mpBegin != out->mpEnd) {
        *out->mpBegin = 0;
        out->mpEnd = out->mpBegin;
    }

    // "C|" drive prefix -> "C:"; otherwise copy the segment verbatim
    if (iswctype((wint_t)seg[0], 0x103) && seg[1] == 0x7c) {
        out->assign(seg, segEnd);
        out->mpBegin[1] = 0x3a;
    } else {
        out->append(seg, segEnd);
    }
    Fn920f00(out);
    return 1;
}

// ===========================================================================
// 0x008e3fa0  ResolveRelativeURL
// ===========================================================================
extern "C" const wchar16 STR_dot_1409f64[];       // 0x01409f64
extern "C" const wchar16 STR_dotdot_1436ea8[];    // 0x01436ea8

// @ 0x008e3fa0
void* Fn8e3fa0(void** out, wchar16* base, wchar16* rel)
{
    WStr* o = (WStr*)out;

    if (o->mpBegin != o->mpEnd) {
        *o->mpBegin = 0;
        o->mpEnd = o->mpBegin;
    }

    if (rel[0] == 0) {                                  // "" -> copy the base
        wchar16* e = base;
        while (*e)
            ++e;
        o->assign(base, e);
        return out;
    }

    if (rel[0] == 0x23) {                               // "#frag"
        wchar16* e = base;
        while (*e)
            ++e;
        o->assign(base, e);
        int pos = o->find(0x23, 0);
        ((WStrErase*)o)->Fn8e3a70((uint32)pos, 0xffffffffu);
        wchar16* re = rel;
        while (*re)
            ++re;
        o->append(rel, re);
        return out;
    }

    if (Fn8e38b0(rel) != 0) {                           // rel carries its own scheme
        o->assignCStr(rel);
        return out;
    }

    wchar16* p = base;                                  // resolved so far
    int scheme = (int)(size_t)Fn8e38b0(base);
    if (scheme != 0) {
        p = (wchar16*)((char*)(size_t)scheme + 2);      // past "scheme:"
        o->assign(base, p);
    }

    if (rel[0] != 0x2f || rel[1] != 0x2f) {
        wchar16* q = p;                                 // base authority prefix
        if (p[0] == 0x2f && p[1] == 0x2f) {
            q = Fn8e3900(p + 2);                        // skip "//host"
            o->assign(p, q);
        }
        if (rel[0] != 0x2f) {
            wchar16* dirEnd = Fn8e3960(q);              // end of base's directory
            wchar16* segEnd = Fn8e3960(rel);            // end of rel's first segment
            o->append(q, dirEnd);
            if (rel < segEnd) {
                // relative path: resolve "." / ".." segments
                Fn8e3a10((int*)o, (int)(dirEnd - base));
                wchar16* c0 = rel;                      // segment start
                wchar16* c1 = rel + 1;
                wchar16* c2 = rel + 2;
                do {
                    if (*c0 != 0x2e) {
                        o->appendChar(*c0);
                        ++c0; ++c1; ++c2;
                        continue;
                    }
                    if (*c1 == 0x2f) {                  // "./"
                        c0 += 2; c1 += 2; c2 += 2;
                        continue;
                    }
                    if (c1 == segEnd) {
                        ++c0; ++c1; ++c2;
                        continue;
                    }
                    if (*c1 != 0x2e) {
                        o->appendChar(*c0);
                        ++c0; ++c1; ++c2;
                        continue;
                    }
                    if (*c2 == 0x2f) {                  // "../"
                        c0 += 3; c1 += 3; c2 += 3;
                        if (Fn8e3a10((int*)o, (int)(dirEnd - base)) == 0)
                            o->appendCStr(STR_dot_1409f64);
                    } else {
                        if (c2 != segEnd) {
                            o->appendChar(*c0);
                            ++c0; ++c1; ++c2;
                            continue;
                        }
                        c0 += 2; c1 += 2; c2 += 2;      // ".."
                        if (Fn8e3a10((int*)o, (int)(dirEnd - base)) == 0)
                            o->appendCStr(STR_dotdot_1436ea8);
                    }
                } while (c0 < segEnd);
            } else if (rel[0] != 0x3b) {
                // no path: carry over the base's ";params" / "?query" / "#frag"
                wchar16* s = dirEnd;
                if (rel[0] != 0x3b) {
                    if (s[0] == 0x3b) {
                        int w = iswctype(0x3b, 0x157);
                        while (w != 0 && s[0] != 0x3f && s[0] != 0x23) {
                            o->appendChar(s[0]);
                            ++s;
                            w = iswctype(s[0], 0x157);
                        }
                    }
                    if (rel[0] != 0x3f) {
                        if (s[0] == 0x3f) {
                            int w = iswctype(0x3f, 0x157);
                            while (w != 0 && s[0] != 0x23) {
                                o->appendChar(s[0]);
                                ++s;
                                w = iswctype(s[0], 0x157);
                            }
                        }
                        if (rel[0] != 0x23) {
                            if (s[0] == 0x23) {
                                int w = iswctype(0x23, 0x157);
                                while (w != 0) {
                                    o->appendChar(s[0]);
                                    ++s;
                                    w = iswctype(s[0], 0x157);
                                }
                            }
                            return out;
                        }
                    }
                }
            }
        }
    }
    o->appendCStr(rel);
    return out;
}

// ===========================================================================
// 0x008e3100  Document::LoadResource
// ===========================================================================
struct StackAlloc {
    char* mpCurrentObjectBegin;   // +0x00
    char* mpCurrentObjectEnd;     // +0x04
    char* mpCurrentBlockEnd;      // +0x08
    void* AllocateNewBlock(uint32 bytes);   // 0x00928ba0
};

struct ResourceDoc {
    char       _pad00[0x08];
    StackAlloc mAllocator;        // +0x08
    char       _pad14[0x34 - 0x14];
    void*      mpResourceProvider;  // +0x34
    char       _pad38[0x48 - 0x38];
    wchar16*   mpBaseURI;           // +0x48
    wchar16*   mpDocumentURI;       // +0x4c
    char       _pad50[0x100 - 0x50];
    void*      mResourceTableBegin; // +0x100
    void*      mResourceTableEnd;   // +0x104
    char       _pad108[0x118 - 0x108];
    void*      mpErrorListener;     // +0x118
};

struct ResourceProvider {
    virtual void* r0(); virtual void* r1();
    virtual void* Load(void* out, void* url, void* cb, void* self,
                       void* listener, int flags);          // +0x04
};

struct AutoRef { void* mpObject; };      // +0x00

extern "C" void  Fn8e2ae0();                    // 0x008e2ae0  load callback

// @ 0x008e3100
void __fastcall Fn8e3100(void* pThis, int param_2, void* param_3, void* param_4,
                         char param_5, int param_6)
{
    ResourceDoc* doc = (ResourceDoc*)pThis;
    if (doc->mpResourceProvider == 0)
        return;

    wchar16* url[2];                       // eastl fixed string on the stack
    url[0] = 0;
    url[1] = 0;
    wchar16* base = doc->mpBaseURI;
    if (base == 0)
        base = doc->mpDocumentURI;
    Fn8e3fa0((void**)url, base, (wchar16*)param_2);

    AutoRef* ref;
    if ((doc->mAllocator.mpCurrentBlockEnd - doc->mAllocator.mpCurrentObjectBegin) >= 0x18) {
        ref = (AutoRef*)doc->mAllocator.mpCurrentObjectBegin;
        doc->mAllocator.mpCurrentObjectBegin = (char*)ref + 0x18;
        doc->mAllocator.mpCurrentObjectEnd   = (char*)ref + 0x18;
        if (ref != 0) {
            ref[1].mpObject = 0;
            ref[0].mpObject = 0;
        }
    } else {
        ref = (AutoRef*)doc->mAllocator.AllocateNewBlock(0x18);
    }

    ref[2].mpObject = param_3;
    ref[4].mpObject = param_4;
    *(char*)&ref[3].mpObject = param_5;
    ref[5].mpObject = 0;
    ref[1].mpObject = doc->mResourceTableEnd;
    ref[0].mpObject = (void*)&doc->mResourceTableBegin;
    doc->mResourceTableEnd = ref;
    *(void**)(ref[1].mpObject) = ref;

    void* listener = doc->mpErrorListener;
    void* self = doc;
    ((ResourceProvider*)doc->mpResourceProvider)->Load(&ref[5], (void*)url, (void*)&Fn8e2ae0,
                                                       self, listener, param_6);
    if (listener != 0 && listener != (void*)&Fn8e2ae0 && listener != self)
        operator_delete__(listener);
}

// ===========================================================================
// 0x008e3660  Document::GetStylesheets (recursive element walk)
// ===========================================================================
// EASTL intrusive-list node.  The child-list anchor is embedded at +0x14,
// its link fields are { mpParent(+0x14), mChildHead(+0x18) }; a node's own
// sibling link lives at +0x04 and its owner is (link - 4).
struct DomNode {
    void*     mpVtable;       // +0x00
    DomNode*  mpSiblingLink;  // +0x04
    char      _pad08[0x14 - 0x08];
    DomNode*  mpParent;       // +0x14  (child-list anchor: mpPrev)
    DomNode*  mChildHead;     // +0x18  (child-list anchor: mpNext)
    char      _pad1c[0x28 - 0x1c];
    int       mElementType;   // +0x28
    int       Type();         // 0x00fc7e50  Node::Type
};

static const int kElementType_Style = 7;
static const int kElementType_Link  = 8;
static const int kNodeType_Element  = 1;

struct Stylesheet {
    virtual void* sAddRef();     // +0x00
    virtual void* sRelease();    // +0x04
};

struct StylesheetProvider {
    virtual void* p00(); virtual void* p01(); virtual void* p02();
    virtual Stylesheet* resolve(int key);        // +0x0c
};

struct StyleVec {
    void* mpBegin;              // +0x00
    void* mpEnd;                // +0x04
    void* mpCapacity;           // +0x08
    void  erase(void* first, void* last);        // 0x00e25bd0
};

struct DomElement {
    void* FindChildNodeByName(const wchar16* name, int flags);   // 0x008e4480
    wchar16* GetAttrValue(const wchar16* attr);                  // 0x008e45b0
};

static wchar16* Fn8e45b0_helper(DomNode* e, const wchar16* attr)
{
    return ((DomElement*)e)->GetAttrValue(attr);
}

extern "C" const wchar16 STR_head_1436e7c[];      // 0x01436e7c  L"head"
extern "C" void* Fn8e42d0_get(void* elem);                       // 0x008e42d0
extern "C" void  Fn8e3230(void* pos, void* val);                 // 0x008e3230
extern "C" void* Fn8e3620(void* vec, void* val);                 // 0x008e3620
extern "C" const wchar16 STR_attr_a_13f36a8[];                   // 0x013f36a8  L"rel"
extern "C" const wchar16 STR_attr_b_13f36bc[];                   // 0x013f36bc  L"type"
extern "C" const wchar16 STR_stylesheet_1436e34[];               // 0x01436e34  L"stylesheet"
extern "C" const wchar16 STR_textcss_1436e68[];                  // 0x01436e68  L"text/css"
extern "C" const wchar16 STR_root_13fa030[];                     // 0x013fa030  L"/"

struct Document {
    char          _pad00[0x2c];
    unsigned char mbDocumentChanged;  // +0x2c
    char          _pad2d[0x40 - 0x2d];
    DomElement*   mpDocumentElement;  // +0x40
    StyleVec      mStylesheets;       // +0x50
    char          _pad5c[0xa8 - 0x5c];
    StyleVec      mUserStylesheets;   // +0xa8
};

// @ 0x008e3660
void __fastcall Fn8e3660(void* pThis, void* elem)
{
    Document* doc = (Document*)pThis;
    DomNode*  e   = (DomNode*)elem;

    if (e->mElementType == kElementType_Style) {
        StylesheetProvider* q = (StylesheetProvider*)Fn8e42d0_get(e);
        if (q == 0)
            return;
        Stylesheet* s = q->resolve(0x23faacf);
        if (s == 0)
            return;
        s->sAddRef();
        Stylesheet** end = (Stylesheet**)doc->mStylesheets.mpEnd;
        if (end < (Stylesheet**)doc->mStylesheets.mpCapacity) {
            doc->mStylesheets.mpEnd = (void*)(end + 1);
            if (end != 0) {
                *end = s;
                s->sAddRef();
            }
        } else {
            Fn8e3230(end, &s);
        }
        if (s != 0)
            s->sRelease();
        return;
    }

    if (e->mElementType == kElementType_Link) {
        wchar16* v = Fn8e45b0_helper(e, STR_attr_a_13f36a8);
        bool ok;
        if (v == STR_stylesheet_1436e34)
            ok = true;
        else if (v != 0 && _wcsicmp((const wchar_t*)v, (const wchar_t*)STR_stylesheet_1436e34) == 0)
            ok = true;
        else {
            v = Fn8e45b0_helper(e, STR_attr_b_13f36bc);
            if (v == STR_textcss_1436e68)
                ok = true;
            else if (v == 0)
                ok = false;
            else
                ok = (_wcsicmp((const wchar_t*)v, (const wchar_t*)STR_textcss_1436e68) == 0);
        }
        if (!ok)
            return;
        StylesheetProvider* q = (StylesheetProvider*)Fn8e42d0_get(e);
        if (q == 0)
            return;
        Stylesheet* s = q->resolve(0x23faacf);
        if (s == 0)
            return;
        s->sAddRef();
        Fn8e3620(&doc->mStylesheets, &s);
        if (s != 0)
            s->sRelease();
        return;
    }

    // generic element: recurse into the sibling chain of the child list
    DomNode* stop = (DomNode*)((char*)e + 0x14);      // owner of the child anchor
    DomNode* child = e->mChildHead != 0 ? (DomNode*)((char*)e->mChildHead - 4) : 0;
    for (;;) {
        if (child == stop)
            break;
        if (child->Type() == kNodeType_Element)
            Fn8e3660(pThis, child);
        child = child->mpSiblingLink != 0 ? (DomNode*)((char*)child->mpSiblingLink - 4) : 0;
    }
}

// ===========================================================================
// 0x008e37e0  Document::Stylesheets
// ===========================================================================
// @ 0x008e37e0
void* __fastcall Fn8e37e0(Document* pThis)
{
    if (pThis->mbDocumentChanged != 0) {
        pThis->mStylesheets.erase(pThis->mStylesheets.mpBegin, pThis->mStylesheets.mpEnd);
        Fn8e2f30((int*)pThis->mStylesheets.mpEnd,
                 (char*)pThis->mUserStylesheets.mpBegin,
                 (char*)pThis->mUserStylesheets.mpEnd,
                 (char*)pThis);
        if (pThis->mpDocumentElement != 0) {
            void* head = pThis->mpDocumentElement->FindChildNodeByName(STR_head_1436e7c, 0);
            if (head != 0)
                Fn8e3660((void*)pThis, head);
        }
        pThis->mbDocumentChanged = 0;
    }
    return (void*)&pThis->mStylesheets;
}

// ===========================================================================
// 0x008e42c0  has-pending-stylesheet
// ===========================================================================
// @ 0x008e42c0
int __fastcall Fn8e42c0(void* p)
{
    return *(int*)((char*)p + 0x2c) != -1;
}

// ===========================================================================
// 0x008e42d0  free pending stylesheet
// ===========================================================================
struct StylesheetQueue {
    void Fn8e42e0(void* arg);       // @ 0x008e42e0 (thiscall)
    void Fn8e2900(int id);          // 0x008e2900 (thiscall)
    void Fn8e28b0(int id, void* arg); // 0x008e28b0 (thiscall)
};

// @ 0x008e42d0
void __fastcall Fn8e42d0(void* p)
{
    void* sub = *(void**)((char*)p + 0x10);
    int   id  = *(int*)((char*)p + 0x2c);
    ((StylesheetQueue*)sub)->Fn8e2900(id);
}

// ===========================================================================
// 0x008e42e0  enqueue stylesheet
// ===========================================================================
// @ 0x008e42e0
void StylesheetQueue::Fn8e42e0(void* arg)
{
    char* c = (char*)this;
    if (*(int*)(c + 0x2c) == -1) {
        *(int*)(c + 0x2c) = Fn8e3850(*(void**)(c + 0x10));
    }
    void* sub = *(void**)(c + 0x10);
    int   id  = *(int*)(c + 0x2c);
    ((StylesheetQueue*)sub)->Fn8e28b0(id, arg);
}
