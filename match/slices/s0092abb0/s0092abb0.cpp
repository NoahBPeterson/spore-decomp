// Slice s0092abb0: EA::Clipboard (SetClipboardData, Win32 clipboard window) and
// EA::CommandLine (argument/switch lookup, insert, current app path).
#include "types.h"

typedef unsigned int size_t;

typedef void* HWND;
typedef void* HANDLE;
typedef void* HMODULE;
typedef void* HLOCAL;
typedef void* FARPROC;
typedef const void* LPCVOID;
typedef void* LPVOID;
typedef int BOOL;
typedef unsigned long DWORD;
typedef unsigned int UINT;
typedef long LONG;
typedef const wchar_t* LPCWSTR;
typedef wchar_t* LPWSTR;
typedef const char* LPCSTR;

extern "C" __declspec(dllimport) BOOL __stdcall ChangeClipboardChain(HWND, HWND);
extern "C" __declspec(dllimport) BOOL __stdcall DestroyWindow(HWND);
extern "C" __declspec(dllimport) BOOL __stdcall OpenClipboard(HWND);
extern "C" __declspec(dllimport) BOOL __stdcall CloseClipboard();
extern "C" __declspec(dllimport) BOOL __stdcall IsClipboardFormatAvailable(UINT);
extern "C" __declspec(dllimport) HANDLE __stdcall GetClipboardData(UINT);
extern "C" __declspec(dllimport) LPVOID __stdcall GlobalLock(HANDLE);
extern "C" __declspec(dllimport) BOOL __stdcall GlobalUnlock(HANDLE);
extern "C" __declspec(dllimport) size_t __stdcall GlobalSize(HANDLE);
extern "C" __declspec(dllimport) HWND __stdcall SetClipboardViewer(HWND);
extern "C" __declspec(dllimport) LONG __stdcall SetWindowLongA(HWND, int, LONG);
extern "C" __declspec(dllimport) LONG __stdcall GetWindowLongA(HWND, int);
extern "C" __declspec(dllimport) HWND __stdcall CreateWindowExA(DWORD, LPCSTR, LPCSTR, DWORD, int, int, int, int, HWND, void*, HMODULE, LPVOID);
extern "C" __declspec(dllimport) unsigned short __stdcall RegisterClassA(const void*);
extern "C" __declspec(dllimport) HMODULE __stdcall GetModuleHandleA(LPCSTR);
extern "C" __declspec(dllimport) HMODULE __stdcall GetModuleHandleW(LPCWSTR);
extern "C" __declspec(dllimport) FARPROC __stdcall GetProcAddress(HMODULE, LPCSTR);
extern "C" __declspec(dllimport) DWORD __stdcall GetVersion();
extern "C" __declspec(dllimport) long __stdcall DefWindowProcA(HWND, UINT, unsigned, long);
extern "C" __declspec(dllimport) int __cdecl _wcsicmp(const wchar_t*, const wchar_t*);
extern "C" __declspec(dllimport) wchar_t* __cdecl wcsstr(const wchar_t*, const wchar_t*);

void* operator_new(uint32_t n, const char* name, int a, int b, int c, int d);
void  operator_delete__(void* p);
inline void* operator new(unsigned int, void* p) { return p; }
void* EASTL_allocator_allocate(uint32_t n, const char* name, int flags, unsigned dbg,
                               const char* file, int line);   // 0x00f473a0
void  DoInsertValue(void* dst, const void* src, unsigned n);
void* CopyWStrings(const void* first, const void* last, void* dst);  // 0x84ab40
void  FUN_004228e0(int a, int b);            // 0x4228e0
void  FUN_0042e610(unsigned n);              // 0x42e610
void* FUN_006abeb0(unsigned n);              // 0x6abeb0
void  WString_Assign(void* s, const void* first, const void* last); // 0x423650
void  WStr_Append(void* s, const wchar_t* first, const wchar_t* last); // 0x429580
void  WStr_PushBack(void* s, wchar_t c);     // 0x4f6510
void  WStr_RangeInitialize(void* s, const wchar_t* p); // 0x579a90
void* WStr_Find(const void* s, const wchar_t* sub, int start); // 0x608340
void  Stristr16();                           // 0x92cc90 (placeholder)
int   Stristr16_real(const wchar_t* s, const wchar_t* sub); // 0x92cc90
void  Mutex_Lock(void* m, void* name);       // 0x9221b0
void  Mutex_Unlock(void* m);                 // 0x922270
void  Clipboard_Clear(void* c, unsigned type); // 0x92a940
void  Win32Clipboard_WriteText(void* w, const wchar_t* t, int n); // 0x92aa20
void* FUN_009289f0(int size, int a, int b, int c, int d, int e); // 0x9289f0
void* FUN_0092aae0(void* text, int n);       // 0x92aae0
void* FUN_0092aa20;                          // unused

typedef long LRESULT_DEF;

// ---------------------------------------------------------------- strings
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

// ---------------------------------------------------------------- Clipboard
struct Mutex { char pad[0x14]; void Lock(void* name) { Mutex_Lock(this, name); } void Unlock() { Mutex_Unlock(this); } };
struct DataInfo { unsigned mnType; void* mpData; };
struct IData {
    virtual void i0();
    virtual void i1();                 // +0x04
    virtual void i2();
    virtual unsigned i3();             // +0x0c
    virtual const wchar_t* i4(int n);  // +0x10
    virtual unsigned i5();             // +0x14
};

struct Clipboard {
    void** vftable;                 // +0
    int mnId;                       // +4
    void* mpOSData;                 // +8
    DataInfo mDataInfoArray[0x20];  // +0xc
    char pad10c[0xc];               // +0x10c .. 0x117
    Mutex mMutex;                   // +0x118
    char pad12c[0x20];              // +0x12c .. 0x14b
    bool mbFlag;                    // +0x14c
    char pad14d[3];
    void Clear(unsigned type);                    // 0x92a940 (other slice)
    bool SetClipboardData(IData* pData, bool b);  // @ 0092abb0
};

struct Win32Clipboard {
    bool mbEnabled;      // +0
    char pad01[3];
    int mnGettingText;   // +4
    int mnSettingText;   // +8
    Clipboard* mpPrimary; // +0xc
    HWND mHWND;          // +0x10
    HWND mNextHWND;      // +0x14
    DWORD mnLocale;      // +0x18
    Win32Clipboard(Clipboard* owner);   // @ 0092afb0
    bool WindowProcedure(WString* text); // @ 0092adb0
    void Destroy();                       // @ 0092ad10
};

// global AutoOSGlobalPtr-like object with the Clipboard at +0x10
extern void* g_ClipboardAutoPtr;   // 0x1668f00

// ---------------------------------------------------------------- CommandLine
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

// ---------------------------------------------------------------- bodies
// @ 0x0092ac90  publish the process-global Clipboard pointer, returning the old one
void* FUN_0092ac90(void* v) {
    char* g = (char*)g_ClipboardAutoPtr;
    void* old = *(void**)(g + 0x10);
    *(void**)(g + 0x10) = v;
    return old;
}

// @ 0x0092ad10
void Win32Clipboard::Destroy() {
    if (mpPrimary != 0) {
        Win32Clipboard* w = 0;
        (void)w;
    }
    // actual object is this->mpPrimary? see note: this routine uses +8 of the owning Clipboard
}

// @ 0x0092ad10  (as written on the Clipboard's platform object)
void DestroyPlatformClipboard(void* owner) {
    char* o = (char*)owner;
    char* p = *(char**)(o + 8);
    if (p != 0) {
        if (*(void**)(p + 0x10) != 0) {
            ChangeClipboardChain(*(HWND*)(p + 0x10), *(HWND*)(p + 0x14));
            DestroyWindow(*(HWND*)(p + 0x10));
        }
        operator_delete__(p);
        *(void**)(o + 8) = 0;
    }
}

// @ 0x0092ad50
void* FUN_0092ad50(bool create) {
    char* g = (char*)g_ClipboardAutoPtr;
    if (*(void**)(g + 0x10) == 0 && create) {
        void* mem = operator_new(0x150, "Clipboard", 0, 0, 0, 0);
        if (mem != 0) {
            void* obj = 0;
            (void)obj;
        }
    }
    return *(void**)(g + 0x10);
}

// @ 0x0092afb0
Win32Clipboard::Win32Clipboard(Clipboard* owner) {
    mbEnabled = true;
    mnGettingText = 0;
    mnSettingText = 0;
    mpPrimary = owner;
    mHWND = 0;
    mNextHWND = 0;
    mnLocale = 0x409;
    GetVersion();
    if (mbEnabled != false) {
        char wc[0x28];
        *(void**)(wc + 0x0) = 0;
        *(void**)(wc + 0x4) = 0;
        *(void**)(wc + 0x8) = 0;
        *(void**)(wc + 0xc) = 0;
        *(void**)(wc + 0x10) = (void*)0x92ae80;
        *(void**)(wc + 0x14) = 0;
        *(void**)(wc + 0x18) = 0;
        *(void**)(wc + 0x1c) = (void*)4;
        *(void**)(wc + 0x20) = 0;
        *(void**)(wc + 0x24) = 0;
        RegisterClassA(wc);
        mHWND = CreateWindowExA(0, "EAClipboardClass", "EAClipboard", 0,
                                (int)0x80000000, (int)0x80000000, (int)0x80000000, (int)0x80000000,
                                0, 0, GetModuleHandleA(0), 0);
        if (mHWND != 0) {
            SetWindowLongA(mHWND, -0x15, (LONG)this);
            mNextHWND = SetClipboardViewer(mHWND);
        }
    }
}

// @ 0x0092adb0
bool Win32Clipboard::WindowProcedure(WString* text) {
    bool result = false;
    bool got = false;
    if (text->mpBegin != text->mpEnd) {
        *text->mpBegin = 0;
        text->mpEnd = text->mpBegin;
    }
    if (mbEnabled && mnSettingText == 0) {
        ++mnGettingText;
        if (OpenClipboard(0)) {
            if (IsClipboardFormatAvailable(0xd)) {
                HANDLE h = GetClipboardData(0xd);
                if (h != 0) {
                    wchar_t* p = (wchar_t*)GlobalLock(h);
                    if (p != 0) {
                        size_t n = GlobalSize(h) >> 1;
                        WString_Assign(text, text->mpBegin, text->mpEnd);
                        wchar_t* end = p + n;
                        while (p < end && *p != 0) {
                            text->push_back(*p);
                            ++p;
                        }
                        GlobalUnlock(h);
                        got = true;
                    }
                }
            }
            CloseClipboard();
        }
        --mnGettingText;
    }
    return result || got;
}

// @ 0x0092abb0
bool Clipboard::SetClipboardData(IData* pData, bool b) {
    mMutex.Lock((void*)0x143e3a0);
    if (b)
        Clear(0xffffffff);
    if (pData != 0) {
        pData->i1();
        unsigned type = pData->i3();
        Clear(type);
        unsigned i = 0;
        for (; i < 0x20; ++i) {
            if (mDataInfoArray[i].mnType == 0) {
                mDataInfoArray[i].mnType = type;
                mDataInfoArray[i].mpData = pData;
                break;
            }
        }
        if (i == 0x20) {
            Clear(mDataInfoArray[0].mnType);
            mDataInfoArray[0x1f].mnType = type;
            mDataInfoArray[0x1f].mpData = pData;
        }
        if (mnId == 1 && type == 3 && mpOSData != 0) {
            mMutex.Unlock();
            unsigned n = pData->i5();
            int len = (int)(n >> 1) - 1;
            const wchar_t* t = pData->i4(len);
            Win32Clipboard_WriteText(mpOSData, t, len);
            mMutex.Lock((void*)0x143e3a0);
        }
    }
    mMutex.Unlock();
    return true;
}

// @ 0x0092acb0
bool SetClipboardText(Clipboard* clipboard, const wchar_t* s, int len) {
    char result = 0;
    void* mem = FUN_009289f0(len * 2 + 0x1a, 0, 0, 0, 0, 0);
    if (mem != 0) {
        IData* obj = (IData*)FUN_0092aae0((void*)s, len);
        if (obj != 0) {
            obj->i1();
            result = clipboard->SetClipboardData(obj, true);
            obj->i2();
        }
    }
    return result != 0;
}

// @ 0x0092b0b0
bool Clipboard_EnablePlatform(void* self) {
    char* s = (char*)self;
    if (s[0x14c] != 0 && *(void**)(s + 8) == 0 && *(int*)(s + 4) == 1) {
        void* mem = FUN_006abeb0(0x1c);
        if (mem != 0) {
            *(void**)(s + 8) = new (mem) Win32Clipboard((Clipboard*)self);
            return true;
        }
        *(void**)(s + 8) = 0;
    }
    return true;
}

// @ 0x0092b0f0
void FUN_0092b0f0(char* self, int v) {
    Mutex* m = (Mutex*)(self + 0x118);
    m->Lock((void*)0x143e3a0);
    *(int*)(self + 4) = v;
    if (*self != 0) {
        if (v == 1) {
            Clipboard_EnablePlatform(self);
            m->Unlock();
            return;
        }
        DestroyPlatformClipboard(self);
    }
    m->Unlock();
}

// @ 0x0092b140
bool FUN_0092b140(char* self) {
    Mutex* m = (Mutex*)(self + 0x118);
    m->Lock((void*)0x143e3a0);
    if (*self == 0) {
        *self = 1;
        if (self[0x14c] != 0 && *(void**)(self + 8) == 0 && *(int*)(self + 4) == 1) {
            void* mem = FUN_006abeb0(0x1c);
            if (mem != 0) {
                *(void**)(self + 8) = new (mem) Win32Clipboard((Clipboard*)self);
                m->Unlock();
                return true;
            }
            *(void**)(self + 8) = 0;
        }
    }
    m->Unlock();
    return true;
}

// @ 0x0092b1b0
WString* CommandLine::at(unsigned i) {
    int n = (int)(mpEnd - mpBegin);
    if (i < (unsigned)n)
        return (WString*)((char*)mpBegin + (i << 4));
    return (WString*)((char*)this + 0x28);
}

// @ 0x0092b1d0
CommandLine::CommandLine() {
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

// @ 0x0092b690
CommandLineB::CommandLineB() {
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
WString* VectorEraseWString(void* vec, WString* pos) {
    char* v = (char*)vec;
    if ((char*)pos + 0x10 < *(char**)(v + 4))
        CopyWStrings((char*)pos + 0x10, *(void**)(v + 4), pos);
    *(int*)(v + 4) -= 0x10;
    WString* last = *(WString**)(v + 4);
    if ((((char*)last->mpCapacity - (char*)last->mpBegin) & 0xfffffffe) > 2 && last->mpBegin)
        operator_delete__(last->mpBegin);
    return pos;
}

// @ 0x0092b7b0
void CommandLine::InsertArgument(const wchar_t* arg, unsigned index) {
    unsigned n = (unsigned)((char*)mpEnd - (char*)mpBegin) >> 4;
    if (index > n)
        index = n;
    WString tmp;
    tmp.mpBegin = 0;
    tmp.mpEnd = 0;
    tmp.mpCapacity = 0;
    WStr_RangeInitialize(&tmp, arg);
    void* at = (char*)mpBegin + (index << 4);
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

// @ 0x0092b5f0
int GetCurrentAppPath(WString* out) {
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

// @ 0x0092b200
unsigned CommandLine::FindArgument(const wchar_t* arg, bool exact, bool sub, WString* out, int start) {
    unsigned result = 0xffffffff;
    if (start < 0)
        start = 0;
    unsigned count = (unsigned)((char*)mpEnd - (char*)mpBegin) >> 4;
    if ((unsigned)start < count) {
        for (; (unsigned)start < count; ++start) {
            WString* cur = (WString*)((char*)mpBegin + (start << 4));
            bool hit;
            if (!sub) {
                if (exact)
                    hit = _wcsicmp(cur->mpBegin, arg) == 0;
                else
                    hit = Stristr16_real(cur->mpBegin, arg) != 0;
            } else {
                if (exact)
                    hit = cur->find(arg, 0) != -1;
                else
                    hit = 0;
            }
            if (hit) {
                result = (unsigned)start;
                break;
            }
        }
    }
    if (out != 0) {
        if (result == 0xffffffff) {
            if (out->mpBegin != out->mpEnd) {
                *out->mpBegin = 0;
                out->mpEnd = out->mpBegin;
            }
        } else {
            WString* src = (WString*)((char*)mpBegin + (result << 4));
            out->assign(src->mpBegin, src->mpEnd);
        }
    }
    return result;
}

// @ 0x0092b300  find a switch (starting with '-' or '/') in the argument vector
unsigned CommandLine::FindSwitch(const wchar_t* sw, bool exact, WString* out, unsigned start) {
    if (out != 0 && out->mpBegin != out->mpEnd) {
        *out->mpBegin = 0;
        out->mpEnd = out->mpBegin;
    }
    if ((int)start < 0)
        start = 0;
    // skip leading switch introducer chars
    int k = 0;
    do {
        if (*sw == (wchar_t)"-/"[k]) {
            ++sw;
            break;
        }
        ++k;
    } while (k < 2);
    const wchar_t* p = sw;
    while (*p) ++p;
    unsigned len = (unsigned)(p - sw);
    unsigned count = (unsigned)((char*)mpEnd - (char*)mpBegin) >> 4;
    if (len != 0 && start < count) {
        for (; start < count; ++start) {
            WString* cur = (WString*)((char*)mpBegin + (start << 4));
            if (out != 0) {
                out->assign(sw, sw + len);
            }
            return start;
        }
    }
    return 0xffffffff;
}

// @ 0x0092b4d0  rebuild the command line, quoting arguments that contain spaces
void FUN_0092b4d0(WString* cmdline, WString* args) {
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
