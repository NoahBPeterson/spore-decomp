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

// @ 0x008e2dd0
void* __fastcall Fn8e2dd0(int* pThis, int param_2) // placeholder; see Fn8e2dd0_impl
{
    return pThis;
}

// ===========================================================================
// 0x008e2f30  vector<bool,...> insert helper (EASTL) -- approximated
// ===========================================================================
extern "C" void Fn829110(void*, void*, void*, void*, void*);   // 0x00829110
extern "C" void Fnac97a0(void*, void*, void*);                 // 0x00ac97a0
extern "C" void* operator_new(int);                            // CRT new (0x00f4...)

// @ 0x008e2f30
void Fn8e2f30(int* pThis, char* first, char* last, char* pos)
{
    if (pos == last) return;
    int* begin = (int*)pThis[0];
    int* end   = (int*)pThis[1];
    uint32 n = (uint32)((last - pos) >> 2);
    if (n <= (uint32)((char*)end - (char*)begin >> 2)) {
        uint32 off = (uint32)(((char*)end - first) >> 2);
        if (off <= n) {
            char* mid = pos + off * 4;
            Fn829110(0, mid, last, 0, 0);
            pThis[1] = pThis[1] + (int)((n - off) * 4);
            Fn829110(0, first, 0, 0, 0);
            pThis[1] = pThis[1] + (int)(off * 4);
            Fnac97a0(pos, mid, first + off * 4);
            return;
        }
    }
}

// ===========================================================================
// 0x008e3380  Document::FetchResources (recursive) -- approximated
// @ 0x008e3600  Document::Fn8e3600
// ===========================================================================
struct Doc {
    void Fn8e3380(void* elem, void* arg);   // @ 0x008e3380
    void Fn8e3600(void* arg);               // @ 0x008e3600
};

// @ 0x008e3380
__declspec(noinline) void Doc::Fn8e3380(void* elem, void* arg)
{
    (void)elem; (void)arg;
    *(volatile int*)((char*)this + 0x40) = 0;
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
extern "C" void Fn962210(void* end, void** out);   // 0x00962210
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
        Fn962210(end, (void**)&local);
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
    while (p > limit) {
        p -= 1;
        if (*p == 0x2f) break;
    }
    if (p != end) {
        memmove(p, end, 2);
        strObj[1] = (int)(strObj[1] + ((char*)end - (char*)p) );
    }
    return 1;
}

// ===========================================================================
// 0x008e3a70  basic_string::erase(pos, count)
// ===========================================================================
// @ 0x008e3a70
int* Fn8e3a70(int* pThis, uint32 pos, uint32 count)
{
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
    return pThis;
}

// ===========================================================================
// 0x008e3b90  ConvertURLToFilePath -- approximated
// ===========================================================================
extern "C" int   Fn920f00(void*);                  // 0x00920f00
extern "C" void  Fn678ff0(wchar16*);               // 0x00678ff0
extern "C" void  Fn5d6fc0(void*);                  // 0x005d6fc0
extern "C" char  Fn8e3f10(wchar16);                // 0x008e3f10

// @ 0x008e3b90
uint32 Fn8e3b90(wchar16* url, int* outStr)
{
    if (url == 0) return 0;
    wchar16* scheme = (wchar16*)Fn8e38b0(url);
    if (scheme && _wcsnicmp((const wchar_t*)url, L"file:", 5) == 0) {
        url = scheme + 1;
    }
    (void)outStr;
    return 1;
}

// ===========================================================================
// 0x008e3fa0  ResolveRelativeURL -- approximated
// ===========================================================================
// @ 0x008e3fa0
void* Fn8e3fa0(void** out, wchar16* base, wchar16* rel)
{
    (void)base; (void)rel;
    if (out) { *out = 0; }
    return out;
}

// ===========================================================================
// 0x008e3100  Document::LoadResource -- approximated
// ===========================================================================
// @ 0x008e3100
void __fastcall Fn8e3100(void* pThis, int param_2, void* p3, void* p4, char p5, int param_6)
{
    (void)pThis; (void)param_2; (void)p3; (void)p4; (void)p5; (void)param_6;
}

// ===========================================================================
// 0x008e3660  Document::GetStylesheets -- approximated
// ===========================================================================
// @ 0x008e3660
void __fastcall Fn8e3660(void* pThis, void* elem)
{
    (void)pThis; (void)elem;
}

// ===========================================================================
// 0x008e37e0  Document::Stylesheets
// ===========================================================================
// @ 0x008e37e0
void* __fastcall Fn8e37e0(void* pThis)
{
    char* c = (char*)pThis;
    if (*(unsigned char*)(c + 0x28)) {
        *(unsigned char*)(c + 0x28) = 0;
    }
    return (void*)(c + 0x50);
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
