// src/game/UTFSpore_Win32/EACommandLine.cpp -- migrated from slice(s) s0092abb0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EACommandLine.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/CommandLine.h"

// ---- items of slice s0092abb0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void* HMODULE;
typedef void* FARPROC;
typedef unsigned long DWORD;
typedef const wchar_t* LPCWSTR;
typedef const char* LPCSTR;
extern "C" __declspec(dllimport) HMODULE __stdcall GetModuleHandleW(LPCWSTR);
extern "C" __declspec(dllimport) FARPROC __stdcall GetProcAddress(HMODULE, LPCSTR);
void  operator_delete__(void* p);
void* CopyWStrings(const void* first, const void* last, void* dst);  // 0x84ab40
void  FUN_004228e0(int a, int b);            // 0x4228e0
void  WString_Assign(void* s, const void* first, const void* last); // 0x423650
void  WStr_Append(void* s, const wchar_t* first, const wchar_t* last); // 0x429580
void  WStr_PushBack(void* s, wchar_t c);     // 0x4f6510
void  WStr_RangeInitialize(void* s, const wchar_t* p); // 0x579a90
void* WStr_Find(const void* s, const wchar_t* sub, int start); // 0x608340
struct WString {
    wchar_t* mpBegin;    // +0
    wchar_t* mpEnd;      // +4
    wchar_t* mpCapacity; // +8
    void* mAlloc;        // +0xc
    WString() { mpBegin = mpEnd = (wchar_t*)0x1667bac; mpCapacity = (wchar_t*)0x1667bae; }
    void assign(const wchar_t* first, const wchar_t* last) { WString_Assign(this, first, last); }
    void append(const wchar_t* first, const wchar_t* last) { WStr_Append(this, first, last); }
    void push_back(wchar_t c) { WStr_PushBack(this, c); }
    long find(const wchar_t* s, int start) { return (long)WStr_Find(this, s, start); }
};
struct WStringVector {
    int pad0;
    WString* mpEnd;
    WString* mpCap;
    WString* Erase(WString* pos);
};
struct CommandLine {
    virtual void c0();   // +0 vtable
    WString* mpBegin;    // +4
    WString* mpEnd;      // +8
    WString* mpCapacity; // +0xc
    void* pad10;
    void* pad14;
    WString msCommandLine; // +0x18
    WString msOther;       // +0x28
    CommandLine();         // @ 0092b1d0
    WString* at(unsigned i);                 // @ 0092b1b0
    unsigned FindArgument(const wchar_t* arg, bool exact, bool sub, WString* out, int start); // @ 0092b200
    unsigned FindSwitch(const wchar_t* sw, bool exact, WString* out, unsigned start); // @ 0092b300
    void InsertArgument(const wchar_t* arg, unsigned index); // @ 0092b7b0
};
struct CommandLineB : CommandLine {
    CommandLineB();        // @ 0092b690
};
// ---- items of slice s0092abb0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" __declspec(dllimport) HMODULE __stdcall GetModuleHandleW(LPCWSTR);
extern "C" __declspec(dllimport) FARPROC __stdcall GetProcAddress(HMODULE, LPCSTR);

// @ 0x0092b4d0
void FUN_0092b4d0(WString* cmdline, WString* args)
{
    FUN_004228e0(0, 0xffffffff);
    unsigned count = (unsigned)((char*)args->mpEnd - (char*)args->mpBegin) >> 4;
    for (unsigned i = 0; i < count; ++i) {
        WString* cur = (WString*)((char*)args->mpBegin + (i << 4));
        const wchar_t* s = cur->mpBegin;
        bool quote = false;
        for (const wchar_t* q = s; *q; ++q) {
            if (*q == L' ' || *q == L'\t' || *q == L'\n' || *q == L'\r') {
                quote = true;
                break;
            }
        }
        if (quote)
            WStr_PushBack(cmdline, L'"');
        WStr_Append(cmdline, cur->mpBegin, cur->mpEnd);
        if (quote)
            WStr_PushBack(cmdline, L'"');
        if (i + 1 < count)
            WStr_PushBack(cmdline, L' ');
    }
}

// @ 0x0092b5f0
int GetCurrentAppPath(WString* out)
{
    static FARPROC s_pGetModuleFileNameW = 0;
    static char s_init = 0;
    if (!s_init) {
        HMODULE h = GetModuleHandleW(L"Kernel32.dll");
        if (h != 0)
            s_pGetModuleFileNameW = GetProcAddress(h, "GetModuleFileNameW");
        s_init = 1;
    }
    if (s_pGetModuleFileNameW != 0) {
        wchar_t path[0x104];
        if (((DWORD(__stdcall*)(HMODULE, wchar_t*, DWORD))s_pGetModuleFileNameW)(0, path, 0x104) != 0) {
            wchar_t* p = path;
            if (*p != 0) {
                while (*++p) ;
            }
            out->assign(path, p);
        }
    }
    return (int)((char*)out->mpEnd - (char*)out->mpBegin) >> 1;
}

// @ 0x0092b690
CommandLineB::CommandLineB()
{
    mpBegin = 0;
    mpEnd = 0;
    mpCapacity = 0;
    msCommandLine.mpBegin = (wchar_t*)0x1667bac;
    msCommandLine.mpEnd = (wchar_t*)0x1667bac;
    msCommandLine.mpCapacity = (wchar_t*)0x1667bae;
    msOther.mpBegin = (wchar_t*)0x1667bac;
    msOther.mpEnd = (wchar_t*)0x1667bac;
    msOther.mpCapacity = (wchar_t*)0x1667bae;
}

// @ 0x0092b700
WString* WStringVector::Erase(WString* pos)
{
    char* v = (char*)this;
    if ((char*)pos + 0x10 < *(char**)(v + 4))
        CopyWStrings((char*)pos + 0x10, *(void**)(v + 4), pos);
    *(int*)(v + 4) -= 0x10;
    WString* last = *(WString**)(v + 4);
    if ((((char*)last->mpCapacity - (char*)last->mpBegin) & 0xfffffffe) > 2 && last->mpBegin)
        operator_delete__(last->mpBegin);
    return pos;
}

// @ 0x0092b7b0
void EA::CommandLine::InsertArgument(wchar_t const * arg, int index)
{
    unsigned n = (unsigned)((char*)mStringArray.mpEnd - (char*)mStringArray.mpBegin) >> 4;
    if (index > n)
        index = n;
    eastl::basic_string<wchar_t,eastl::allocator> tmp;
    tmp.mpBegin = 0;
    tmp.mpEnd = 0;
    tmp.mpCapacity = 0;
    WStr_RangeInitialize(&tmp, arg);
    void* at = (char*)mStringArray.mpBegin + (index << 4);
    void* ins = 0;
    (void)at;
    (void)ins;
    if (msCommandLine.mpBegin != msCommandLine.mpEnd) {
        *msCommandLine.mpBegin = 0;
        msCommandLine.mpEnd = msCommandLine.mpBegin;
    }
    if ((((char*)tmp.mpCapacity - (char*)tmp.mpBegin) & 0xfffffffe) > 2 && tmp.mpBegin)
        operator_delete__(tmp.mpBegin);
}
