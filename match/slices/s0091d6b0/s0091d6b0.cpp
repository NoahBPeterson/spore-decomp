// Slice s0091d6b0: EA::Debug exception handling / callstack reporting
// (ExceptionHandler[Win32], ReportWriter drivers, dbghelp symbol engine) plus the
// EA::Debug::ExceptionHandlerWin32::GetExceptionString switch.
// Optimized module (/O2), old-style or no /GS.
#include "types.h"

typedef unsigned int size_t;

// ---------------------------------------------------------------- win32 types
typedef void* HANDLE;
typedef void* HMODULE;
typedef void* HWND;
typedef void* FARPROC;
typedef int BOOL;
typedef unsigned long DWORD;
typedef unsigned int UINT;
typedef const char* LPCSTR;
typedef char* LPSTR;
typedef unsigned __int64 DWORD64;
typedef unsigned __int64 ULONG64;
typedef long LONG;

struct MINIDUMP_EXCEPTION_INFORMATION {
    DWORD ThreadId;             // +0
    void* ExceptionPointers;    // +4
    BOOL  ClientPointers;       // +8
};

// debug CONTEXT (only the two fields we touch)
struct Context {
    char pad00[0xb8];
    void* Eip;                  // +0xb8
    char padbc[8];
    DWORD Esp;                  // +0xc4
};
struct ExceptionPointers {
    void* ExceptionRecord;      // +0
    Context* ContextRecord;     // +4
};

// dbghelp / kernel32 / msvcr90 imports
extern "C" __declspec(dllimport) DWORD __stdcall SymSetOptions(DWORD);
extern "C" __declspec(dllimport) BOOL  __stdcall SymInitialize(HANDLE, LPCSTR, BOOL);
extern "C" __declspec(dllimport) DWORD64 __stdcall SymLoadModule64(HANDLE, HANDLE, LPCSTR, LPCSTR, DWORD64, DWORD);
extern "C" __declspec(dllimport) BOOL  __stdcall SymCleanup(HANDLE);
extern "C" __declspec(dllimport) BOOL  __stdcall SymGetLineFromAddr64(HANDLE, DWORD64, DWORD*, void*);
extern "C" __declspec(dllimport) BOOL  __stdcall SymGetSymFromAddr64(HANDLE, DWORD64, DWORD64*, void*);
extern "C" __declspec(dllimport) BOOL  __stdcall CloseHandle(HANDLE);
extern "C" __declspec(dllimport) HANDLE __stdcall CreateEventA(void*, BOOL, BOOL, LPCSTR);
extern "C" __declspec(dllimport) HMODULE __stdcall LoadLibraryA(LPCSTR);
extern "C" __declspec(dllimport) FARPROC __stdcall GetProcAddress(HMODULE, LPCSTR);
extern "C" __declspec(dllimport) DWORD __stdcall GetCurrentThreadId();
extern "C" __declspec(dllimport) DWORD __stdcall GetCurrentProcessId();
extern "C" __declspec(dllimport) HANDLE __stdcall GetCurrentProcess();
extern "C" __declspec(dllimport) HANDLE __stdcall CreateFileA(LPCSTR, DWORD, DWORD, void*, DWORD, DWORD, HANDLE);
extern "C" __declspec(dllimport) BOOL  __stdcall FlushFileBuffers(HANDLE);
extern "C" __declspec(dllimport) BOOL  __stdcall FreeLibrary(HMODULE);
extern "C" __declspec(dllimport) wchar_t* __cdecl wcsncpy(wchar_t*, const wchar_t*, size_t);
extern "C" __declspec(dllimport) char* __cdecl strncpy(char*, const char*, size_t);
extern "C" __declspec(dllimport) int __cdecl _snprintf(char*, size_t, const char*, ...);

// EA / internal helpers (direct calls)
void EA_Text_StrncpyUTF8ToUTF16(void* dst, unsigned n, const void* src, int len); // 0x93cf10
void EA_IO_EnsureTrailingPathSeparator(wchar_t* s, int len);                      // 0x92fe00
unsigned __int64 FUN_0091a1d0();                     // 0x91a1d0
void* FUN_00932060(const void* name);                // 0x932060
void  FUN_00943570(void* p);                         // 0x943570
void  FUN_00942e50(void* a, void* b);                // 0x942e50
void  FUN_0091ed40(void* buf, int n);                // 0x91ed40

// ---------------------------------------------------------------- ReportWriter
// vtable slot offsets used by this module: 1,2,3,4,5,6,7,8,10,14
struct ReportWriter {
    virtual void r00();
    virtual void r01(void* dst, int n);        // +0x04
    virtual bool r02(const char* path);        // +0x08
    virtual void r03();                        // +0x0c
    virtual void r04(const char* section);     // +0x10
    virtual void r05();                        // +0x14
    virtual void r06(const char* section);     // +0x18
    virtual void r07(const char* section);     // +0x1c
    virtual void r08(const char* text, int v); // +0x20
    virtual void r09();                        // +0x24
    virtual void r10(const char* name, const char* value); // +0x28
    virtual void r11(); virtual void r12(); virtual void r13();
    virtual int  r14();                        // +0x38

    // out-of-line members
    void WriteCallStack(Context* ctx);                         // 0x91fca0
    void WriteStackMemoryView(DWORD esp, unsigned n);          // 0x91fe60
    void WriteDisassembly(void* start, unsigned n, void* eip); // 0x91f400
    void WriteSystemInfo();                                    // 0x91ef30
    void WriteApplicationInfo();                               // 0x91f300
    void WriteRegisterValues(Context* ctx);                    // 0x91fa10
    void WriteModuleList();                                    // 0x91f7c0
    void WriteRegisterMemoryView(Context* ctx);                // 0x91fbd0
    int  GetTimeString(char* buf, unsigned n, void* tm);       // 0x91eca0
    int  GetDateString(char* buf, unsigned n, void* tm);       // 0x91ecf0
    int  GetAddressLocationString(void* addr, char* buf, unsigned n); // 0x91ee80
    void Construct();        // 0x91e970
    void Destroy();          // 0x91fe40

    char mPath[256];       // +0x04
    void* mpFile;          // +0x104
    char mBuffer[1024];    // +0x108
    int mnSectionDepth;    // +0x508
};

struct HandlerNode { HandlerNode* mpNext; HandlerNode* mpPrev; void* mClient; };

struct FixedVectorPtr {
    ReportWriter** mpBegin;      // +0
    ReportWriter** mpEnd;        // +4
    ReportWriter** mpCapacity;   // +8
    unsigned size() const { return (unsigned)(mpEnd - mpBegin); }
};

struct ExceptionHandler {
    void* mpPlatformHandler;   // +0x00
    FixedVectorPtr mReportWriters; // +0x04
    char pad10[0x20];          // +0x10 .. +0x2f
    HandlerNode mNode;         // +0x30
    char* mpBuildDescEnd;      // +0x3c
    char pad40[0x0c];          // +0x40 .. +0x4b
    wchar_t mDir[255];         // +0x4c
    void NotifyClients(int action);          // @ 0091e3b0
    void SetReportDirectory(wchar_t* dir);   // @ 0091e040
};

struct ExceptionHandlerWin32 {
    ExceptionHandler* mpOwner;          // +0x00
    ReportWriter* mpReportWriter;       // +0x04
    bool mbEnabled;                     // +0x08
    char pad09[3];
    int mAction;                        // +0x0c
    int mnTerminateReturnValue;         // +0x10
    int mReportFieldMask;               // +0x14
    ExceptionPointers* mpExceptionPointers; // +0x18
    unsigned mpExceptionAddress;        // +0x1c
    void* mPreviousFilter;              // +0x20
    char mTime[0x24];                   // +0x24
    char mBaseReportName[0x40];         // +0x48

    void WriteHeader();                                       // @ 0091e250
    void WriteCallStack();                                    // @ 0091df70
    void WriteMiniDump();                                     // @ 0091e190
    void WriteExtraData();                                    // @ 0091e3e0
    void WriteExceptionReportInternal(ReportWriter* w);       // @ 0091e4b0
    int  GetReportFilePath(char* buf, unsigned n, int type);  // @ 0091e080
    void WriteExceptionReport();                              // @ 0091e5c0
    unsigned GetAddressInfo(unsigned char flags, unsigned long long addr, unsigned* out); // @ 0091d830
    void GetExceptionString(char* buf, unsigned n);           // @ 0091d950
};

// symbol-engine-ish class for the dbghelp helpers
struct SymbolEngine {
    virtual void s0();
    void* mHandle;       // +0x04
    unsigned mLo;        // +0x08
    unsigned mHi;        // +0x0c
    bool Load(const char* path, unsigned extra);  // @ 0091d6b0
    bool Cleanup();                               // @ 0091d760
    SymbolEngine();                               // @ 0091d7a0
    virtual ~SymbolEngine();                      // @ 0091d7d0
};

struct Holder {
    void* mpInner;
    void Set(int a, int b);                       // @ 0091e020
};

// ---------------------------------------------------------------- bodies
// @ 0x0091d6b0
bool SymbolEngine::Load(const char* path, unsigned) {
    char buf[0x104];
    EA_Text_StrncpyUTF8ToUTF16(buf, 0x104, path, -1);
    if ((mLo | mHi) == 0) {
        unsigned __int64 h = FUN_0091a1d0();
        mLo = (unsigned)h;
        mHi = (unsigned)(h >> 32);
    }
    void* mod = FUN_00932060(path);
    SymSetOptions(0x52);
    SymInitialize(mHandle, 0, 0);
    unsigned __int64 r = SymLoadModule64(mHandle, 0, buf, 0, ((unsigned __int64)mHi << 32) | mLo, (DWORD)mod);
    mLo = (unsigned)r;
    mHi = (unsigned)(r >> 32);
    if ((mLo | mHi) != 0)
        return true;
    return false;
}

// @ 0x0091d760
bool SymbolEngine::Cleanup() {
    if (mHandle != 0) {
        SymCleanup(mHandle);
        CloseHandle(mHandle);
        mHandle = 0;
        mLo = 0;
        mHi = 0;
    }
    return true;
}

// @ 0x0091d7a0
SymbolEngine::SymbolEngine() {
    mHandle = 0;
    mLo = 0;
    mHi = 0;
    mHandle = CreateEventA(0, 0, 0, 0);
}

// @ 0x0091d7d0  (scalar deleting destructor)
SymbolEngine::~SymbolEngine() {
    if (mHandle != 0) {
        SymCleanup(mHandle);
        CloseHandle(mHandle);
        mHandle = 0;
        mLo = 0;
        mHi = 0;
    }
}

// @ 0x0091d830
unsigned ExceptionHandlerWin32::GetAddressInfo(unsigned char flags, unsigned long long addr, unsigned* out) {
    unsigned result = 0;
    if (flags & 1) {
        char line[0x18 + 0x40];
        *(unsigned*)line = 0x18;
        if (SymGetLineFromAddr64(0, addr, 0, line)) {
            FUN_00943570(*(void**)(line + 0x10));
            *out = *(unsigned*)(line + 0x14);
            result = 1;
        }
    }
    if (flags & 2) {
        char sym[0x800 + 0x20];
        *(unsigned*)sym = 0x20;
        *(unsigned*)(sym + 0x18) = 0x800;
        if (SymGetSymFromAddr64(0, addr, 0, sym)) {
            out[1] = *(unsigned*)(sym + 0x38);
            result |= 2;
        }
    }
    return result;
}

// @ 0x0091d950  (large exception-code -> string switch; only main arms reproduced)
void ExceptionHandlerWin32::GetExceptionString(char* buf, unsigned n) {
    unsigned code = *(unsigned*)(*(char**)mpExceptionPointers);
    switch (code) {
    case 0xc0000005:
        _snprintf(buf, n, "ACCESS_VIOLATION %s address 0x%08x",
                  *(unsigned*)(*(char**)mpExceptionPointers + 0x14) ? "writing" : "reading",
                  *(unsigned*)(*(char**)mpExceptionPointers + 0x18));
        return;
    case 0xc0000006:
        strncpy(buf, "IN_PAGE_ERROR", n);
        return;
    case 0x80000003:
        strncpy(buf, "BREAKPOINT", n);
        return;
    case 0x80000004:
        strncpy(buf, "SINGLE_STEP", n);
        return;
    default:
        strncpy(buf, "UNKNOWN", n);
        return;
    }
}

// @ 0x0091df70
void ExceptionHandlerWin32::WriteCallStack() {
    mpReportWriter->r06("Call stack");
    mpReportWriter->WriteCallStack(mpExceptionPointers->ContextRecord);
    mpReportWriter->r07("Call stack");
    mpReportWriter->r06("Stack data");
    mpReportWriter->WriteStackMemoryView(mpExceptionPointers->ContextRecord->Esp, 0x100);
    mpReportWriter->r07("Stack data");
    mpReportWriter->r06("Instruction data");
    unsigned eip = (unsigned)mpExceptionPointers->ContextRecord->Eip;
    mpReportWriter->WriteDisassembly((void*)(eip - 0x80), 0x100, (void*)eip);
    mpReportWriter->r07("Instruction data");
}

// @ 0x0091e020
void Holder::Set(int a, int b) {
    if (mpInner != 0) {
        struct Inner { char pad[0xc]; int f0c; int f10; };
        Inner* p = (Inner*)mpInner;
        p->f0c = a;
        p->f10 = b;
    }
}

// @ 0x0091e040
void ExceptionHandler::SetReportDirectory(wchar_t* dir) {
    wcsncpy(mDir, dir, 0xff);
    mDir[254] = 0;
    EA_IO_EnsureTrailingPathSeparator(mDir, -1);
}

// @ 0x0091e080
int ExceptionHandlerWin32::GetReportFilePath(char* buf, unsigned n, int type) {
    char dir[256];
    char names[128];
    char timebuf[64];
    char datebuf[64];
    char ext[16];
    EA_Text_StrncpyUTF8ToUTF16(dir, 0x100, mpOwner->mDir, -1);
    FUN_0091ed40(names, 0x80);
    mpReportWriter->GetTimeString(timebuf, 0x40, mTime);
    mpReportWriter->GetDateString(datebuf, 0x40, mTime);
    const char* fmt;
    if (type == 1) {
        *(unsigned*)ext = 0x6d646d2e;      // ".mdm"
        *(unsigned short*)(ext + 4) = 0x70; // "p"
        fmt = "%s%s %s %s %s minidump%s";
    } else {
        mpReportWriter->r01(ext, 0x10);
        fmt = "%s%s %s %s %s exception%s";
    }
    _snprintf(buf, n, fmt, dir, mBaseReportName, names, datebuf, timebuf, ext);
    buf[n - 1] = 0;
    char* p = buf + 1;
    while (*buf++) ;
    return (int)(buf - p);
}

// @ 0x0091e190
void ExceptionHandlerWin32::WriteMiniDump() {
    HMODULE h = LoadLibraryA("DbgHelp.dll");
    if (h != 0) {
        FARPROC p = GetProcAddress(h, "MiniDumpWriteDump");
        if (p != 0) {
            MINIDUMP_EXCEPTION_INFORMATION info;
            info.ThreadId = GetCurrentThreadId();
            info.ExceptionPointers = mpExceptionPointers;
            info.ClientPointers = 1;
            char path[256];
            GetReportFilePath(path, 0x100, 1);
            HANDLE f = CreateFileA(path, 0x40000000, 0, 0, 2, 0x80000000, 0);
            if (f != (HANDLE)-1) {
                typedef BOOL (__stdcall *WriteDumpFn)(HANDLE, DWORD, HANDLE, DWORD, void*, void*, void*);
                ((WriteDumpFn)p)(GetCurrentProcess(), GetCurrentProcessId(), f, 0, &info, 0, 0);
                FlushFileBuffers(f);
                CloseHandle(f);
            }
        }
    }
    FreeLibrary(h);
}

// @ 0x0091e250
void ExceptionHandlerWin32::WriteHeader() {
    mpReportWriter->r06("Build info");
    if (mpOwner != 0 && mpOwner->mpBuildDescEnd != 0 && *mpOwner->mpBuildDescEnd != 0)
        mpReportWriter->r08(mpOwner->mpBuildDescEnd, 1);
    mpReportWriter->r07("Build info");
    mpReportWriter->r06("System info");
    mpReportWriter->WriteSystemInfo();
    mpReportWriter->r07("System info");
    mpReportWriter->r06("Application info");
    mpReportWriter->WriteApplicationInfo();
    mpReportWriter->r07("Application info");
    mpReportWriter->r06("Exception info");
    char buf[256];
    mpReportWriter->GetDateString(buf, 0x100, mTime);
    mpReportWriter->r10("date", buf);
    mpReportWriter->GetTimeString(buf, 0x100, mTime);
    mpReportWriter->r10("time", buf);
    GetExceptionString(buf, 0x100);
    mpReportWriter->r10("type", buf);
    mpReportWriter->GetAddressLocationString((void*)mpExceptionAddress, buf, 0x100);
    mpReportWriter->r10("address", buf);
    mpReportWriter->r07("Exception info");
}

// @ 0x0091e3b0
void ExceptionHandler::NotifyClients(int action) {
    HandlerNode* sentinel = &mNode;
    for (HandlerNode* n = sentinel->mpNext; n != sentinel; n = n->mpNext) {
        void** client = (void**)n->mClient;
        void** vt = (void**)*client;
        typedef void (__thiscall *Fn)(void*, ExceptionHandler*, int);
        ((Fn)vt[1])(client, this, action);
    }
}

// @ 0x0091e3e0
void ExceptionHandlerWin32::WriteExtraData() {
    mpReportWriter->r06("Extra");
    int start = mpReportWriter->r14();
    if (mpOwner != 0) {
        __try {
            mpOwner->NotifyClients(4);
            mpOwner->NotifyClients(5);
        } __except (1) {
            mpReportWriter->r08("Extra data is not complete due to an exception generated by some client.\r\n", 0);
        }
    }
    if (start == mpReportWriter->r14())
        mpReportWriter->r08("<none>\r\n", 0);
    mpReportWriter->r07("Extra");
}

// @ 0x0091e4b0
void ExceptionHandlerWin32::WriteExceptionReportInternal(ReportWriter* w) {
    if (w != 0) {
        mpReportWriter = w;
        char buf[260];
        GetReportFilePath(buf, 0x104, 0);
        if (mpReportWriter->r02(buf)) {
            mpReportWriter->r04("Exception Report");
            WriteHeader();
            WriteCallStack();
            mpReportWriter->r06("Registers");
            mpReportWriter->WriteRegisterValues(mpExceptionPointers->ContextRecord);
            mpReportWriter->r07("Registers");
            mpReportWriter->r06("Modules");
            mpReportWriter->WriteModuleList();
            mpReportWriter->r07("Modules");
            mpReportWriter->r06("Register memory");
            mpReportWriter->WriteRegisterMemoryView(mpExceptionPointers->ContextRecord);
            mpReportWriter->r07("Register memory");
            WriteExtraData();
            mpReportWriter->r05();
            mpReportWriter->r03();
        }
    }
}

// @ 0x0091e5c0
void ExceptionHandlerWin32::WriteExceptionReport() {
    char local[0x50c];
    ReportWriter* rw = (ReportWriter*)local;
    rw->Construct();
    unsigned n = mpOwner->mReportWriters.size();
    if (n == 0) {
        WriteExceptionReportInternal(rw);
        rw->Destroy();
        return;
    }
    for (int i = 0; i < (int)n; ++i) {
        ReportWriter* w = (unsigned)i < mpOwner->mReportWriters.size()
                              ? mpOwner->mReportWriters.mpBegin[i] : 0;
        WriteExceptionReportInternal(w);
    }
    rw->Destroy();
}
