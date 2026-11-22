// src/game/UTFSpore_Win32/EACommandLine.cpp -- migrated from slice(s) s0092b840, s0092abb0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EACommandLine.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/CommandLine.h"
#include <intrin.h>
#include <ctype.h>

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
struct CommandLineBVtbl;
struct WString {
    wchar_t* mpBegin;    // +0
    wchar_t* mpEnd;      // +4
    wchar_t* mpCapacity; // +8
    void* mAlloc;        // +0xc
    void Reset() { mpBegin = mpEnd = (wchar_t*)0x1667bac; mpCapacity = (wchar_t*)0x1667bae; }
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
    virtual ~CommandLine(); // +0 vtable slot 0
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

// CommandLineB installs its own vtable at +0 after the base's part is built.
// The un-named `this` store on purpose: a `mpVtbl` spelled as a member keeps
// the object's vfptr identity, and cl rejects such a store (C4589 / a /vmg
// vtordisp lands at +0x38 instead). Everything else the base's construction
// wipes is left as retail leaves it.
struct CommandLineBVtbl;
struct CommandLineB : CommandLine {
    CommandLineB();        // @ 0092b690
};
struct CommandLineBVtbl {
    void (*mDtor)(CommandLineB*); // slot 0
};

// The vtable the construction stores at +0.
static CommandLineBVtbl g_CommandLineBVtbl = { 0 };

// ---- items of slice s0092b840 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern wchar_t gEmptyString[];          // 0x01667BAC empty string buffer
extern wchar_t gEmptyStringCapacity[];  // 0x01667BAE empty string + 2
struct WString_s0092_b840 {
    wchar_t* mpBegin;       // +0x00
    wchar_t* mpEnd;         // +0x04
    wchar_t* mpCapacity;    // +0x08
    char mAllocator;        // +0x0c (empty allocator, padding)
    WString_s0092_b840() : mpBegin(gEmptyString), mpEnd(gEmptyString),
                mpCapacity(gEmptyStringCapacity) {}
    void Construct(const WString_s0092_b840& other);                     // 0x0056E2D0 copy ctor (placement)
    void assign(const wchar_t* first, const wchar_t* last);   // 0x00423650 do_assign
    void resize(unsigned count);                              // 0x00429520 resize
    void erase(unsigned pos, unsigned count);                 // 0x004228E0 erase(pos,count)
    void make_lower();                                        // 0x005E8E80 make_lower
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
    void clear() { if (mpBegin != mpEnd) { *mpBegin = 0; mpEnd = mpBegin; } }
    wchar_t& operator[](unsigned i) { return mpBegin[i]; }
};
struct WStringVec {
    WString_s0092_b840* mpBegin;       // +0x00
    WString_s0092_b840* mpEnd;         // +0x04
    WString_s0092_b840* mpCapacity;    // +0x08
    int mAllocator;         // +0x0c
    WStringVec() : mpBegin(0), mpEnd(0), mpCapacity(0) {}
    WString_s0092_b840* erase(WString_s0092_b840* pos);                          // 0x0092B700
    void DoInsertValue(WString_s0092_b840* pos, const WString_s0092_b840& value); // 0x00554C30
};
struct SplitBase {
    WStringVec mArgs;       // +0x04
    int mUnknown14;         // +0x14
    WString_s0092_b840 mText;          // +0x18
    WString_s0092_b840 mEmpty;         // +0x28
    virtual ~SplitBase();
    void Set(const short* s);
    void Set(const char* s);
    void InsertArgument(const wchar_t* arg, int index);    // 0x0092B7B0
    __forceinline SplitBase(const char* s) { Set(s); }
    __forceinline SplitBase(const short* s) { Set(s); }
};
__declspec(noinline, nothrow) void FixCommandLine(SplitBase* cmdline, const wchar_t* arg);
struct Splitable3 : SplitBase {
    Splitable3(const char* s);
};
struct Splitable4 : SplitBase {
    Splitable4(const short* s);
};
// ---- items of slice s0092b840 end

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
    const CommandLineBVtbl* const* pv = (const CommandLineBVtbl* const*)&g_CommandLineBVtbl;
    *(const CommandLineBVtbl* const**)this = pv;
    msCommandLine.Reset();
    msOther.Reset();
}
// ---- items of slice s0092abb0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" __declspec(dllimport) HMODULE __stdcall GetModuleHandleW(LPCWSTR);
extern "C" __declspec(dllimport) FARPROC __stdcall GetProcAddress(HMODULE, LPCSTR);

// @ 0x0092b700
WString* WStringVector::Erase(WString* pos)
{
    char* v = (char*)this;
    if ((char*)pos + 0x10 < *(char**)(v + 4))
        CopyWStrings((char*)pos + 0x10, *(void**)(v + 4), pos);
    *(int*)(v + 4) -= 0x10;
    WString* last = *(WString**)(v + 4);
    int spare = (int)((char*)last->mpCapacity - (char*)last->mpBegin) & 0xfffffffe;   // signed, as the original's jle
    if (spare > 2 && last->mpBegin)
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

// helpers FixCommandLine (0x0092bbe0) uses; the slice keeps them in an anonymous namespace
const wchar_t* FindLastOf(const wchar_t* end, const wchar_t* begin,
                          const wchar_t* patBegin, const wchar_t* patEnd); // 0x005728F0
int MakeLocaleAvailable(const void* a, const void* b);               // 0x0087D9A0
int GetCurrentAppPath(WString_s0092_b840* out);                      // 0x0092B5F0

static unsigned WStrLen(const wchar_t* s) {
    const wchar_t* p = s;
    while (*p) ++p;
    return (unsigned)(p - s);
}

// Index of the last occurrence of any character of `pat` in `s`, or -1.
static int LastIndexOf(const WString_s0092_b840& s, const wchar_t* pat) {
    const wchar_t* end = s.mpBegin + s.size();
    const wchar_t* p = FindLastOf(end, s.mpBegin, pat, pat + 1);
    return (int)(p - s.mpBegin) - 1;
}

// @ 0x0092bbe0
void FixCommandLine(SplitBase* cmdline, const wchar_t* arg) {
    const bool hasArgs = (cmdline->mArgs.mpEnd != cmdline->mArgs.mpBegin);

    WString_s0092_b840 firstArg;
    if (hasArgs) {
        WString_s0092_b840* src = (cmdline->mArgs.mpEnd == cmdline->mArgs.mpBegin)
                           ? &cmdline->mEmpty
                           : cmdline->mArgs.mpBegin;
        if (src != &firstArg)
            firstArg.assign(src->mpBegin, src->mpEnd);
    }

    wchar_t buffer[512];
    buffer[0] = 0;
    for (int k = 1; k < 512; ++k)
        buffer[k] = 0;

    WString_s0092_b840 appPath;
    if (arg != 0) {
        wchar_t* d = buffer;
        const wchar_t* s = arg;
        wchar_t c;
        do { c = *s++; *d++ = c; } while (c);
    } else {
        GetCurrentAppPath(&appPath);
        wchar_t* d = buffer;
        const wchar_t* s = appPath.mpBegin;
        wchar_t c;
        do { c = *s++; *d++ = c; } while (c);
    }

    if (hasArgs) {
        if (appPath.size() == 0)
            appPath.assign(buffer, buffer + WStrLen(buffer));

        // Directory portion of the application path, made lower case.
        WString_s0092_b840 exeDir;
        exeDir.assign(appPath.mpBegin, appPath.mpEnd);
        int slash = LastIndexOf(exeDir, L"/");
        if (slash >= 0)
            exeDir.erase(0, (unsigned)slash + 1);
        slash = LastIndexOf(exeDir, L"\\");
        if (slash >= 0)
            exeDir.erase((unsigned)slash, (unsigned)-1);
        exeDir.make_lower();

        // Directory portion of the first argument, made lower case.
        WString_s0092_b840 argDir;
        argDir.assign(firstArg.mpBegin, firstArg.mpEnd);
        slash = LastIndexOf(argDir, L"/");
        if (slash >= 0 &&
            ((isalpha((unsigned char)argDir[0]) && argDir[1] == L':') ||
             argDir[0] == L'\\' || argDir[0] == L'/'))
            argDir.erase(0, (unsigned)slash + 1);
        slash = LastIndexOf(argDir, L"\\");
        if (slash >= 0)
            argDir.erase((unsigned)slash, (unsigned)-1);
        argDir.make_lower();

        if (MakeLocaleAvailable(&exeDir, &argDir)) {
            if (cmdline->mArgs.mpEnd != cmdline->mArgs.mpBegin) {
                cmdline->mArgs.erase(cmdline->mArgs.mpBegin);
                if (cmdline->mText.mpBegin != cmdline->mText.mpEnd) {
                    *cmdline->mText.mpBegin = 0;
                    cmdline->mText.mpEnd = cmdline->mText.mpBegin;
                }
            }
            cmdline->InsertArgument(appPath.mpBegin, 0);
        } else {
            appPath.assign(buffer, buffer + WStrLen(buffer));
            if (appPath.size() != 0)
                cmdline->InsertArgument(appPath.mpBegin, 0);
        }
    } else {
        appPath.assign(buffer, buffer + WStrLen(buffer));
        if (appPath.size() != 0)
            cmdline->InsertArgument(appPath.mpBegin, 0);
    }
}

// @ 0x0092c1b0
__declspec(noinline) Splitable3::Splitable3(const char* s)
: SplitBase(s) {
    FixCommandLine(this, 0);
}

// @ 0x0092c210
__declspec(noinline) Splitable4::Splitable4(const short* s)
: SplitBase(s) {
    FixCommandLine(this, 0);
}
