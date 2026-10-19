// src/game/UTFSpore_Win32/ExceptionHandler.cpp -- migrated from slice(s) s0091e650, s0091d6b0 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/ExceptionHandler.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Debug/ReportWriter.h"
#include "EA/Dasm/DisassemblerX86.h"
#include <stdarg.h>

// ---- items of slice s0091d6b0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void* HANDLE;
typedef void* HMODULE;
typedef void* FARPROC;
typedef int BOOL;
typedef unsigned long DWORD;
typedef const char* LPCSTR;
struct MINIDUMP_EXCEPTION_INFORMATION {
    DWORD ThreadId;             // +0
    void* ExceptionPointers;    // +4
    BOOL  ClientPointers;       // +8
};
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
extern "C" __declspec(dllimport) BOOL  __stdcall CloseHandle(HANDLE);
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
void EA_Text_StrncpyUTF8ToUTF16(void* dst, unsigned n, const void* src, int len); // 0x93cf10
void EA_IO_EnsureTrailingPathSeparator(wchar_t* s, int len);                      // 0x92fe00
void  FUN_0091ed40(void* buf, int n);                // 0x91ed40
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
struct Holder {
    void* mpInner;
    void Set(int a, int b);                       // @ 0091e020
};
// ---- items of slice s0091d6b0 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" __declspec(dllimport) BOOL  __stdcall CloseHandle(HANDLE);
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

// ---- items of slice s0091e650 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) __int64 __cdecl _time64(__int64*);
extern "C" __declspec(dllimport) void* __cdecl _localtime64(const __int64*);
extern "C" __declspec(dllimport) void* __stdcall SetUnhandledExceptionFilter(void*);
typedef unsigned int UINT;
extern "C" __declspec(dllimport) void* __cdecl memcpy(void*, const void*, size_t);
extern "C" __declspec(dllimport) void* __cdecl memset(void*, int, size_t);
inline void* operator new(unsigned int, void* p) { return p; }
extern "C" __declspec(dllimport) size_t __cdecl strlen(const char*);
extern "C" __declspec(dllimport) BOOL __stdcall TerminateProcess(HANDLE, UINT);
void* EASTL_allocator_allocate(uint32_t n, const char* name, int flags, unsigned dbg,
                               const char* file, int line);   // 0x00f473a0
void  DoInsertValue(void* dst, const void* src, unsigned n);   // 0x011e0744
struct CString {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    void assign(const char* first, const char* last);          // 0x00454cb0
};
struct ReportWriter_s0091_e650 {
    virtual void r00();
    virtual void r01(void*, int);
    virtual bool r02(const char*);
    virtual void r03();
    virtual void r04(const char*);
    virtual void r05();
    virtual void r06(const char*);
    virtual void r07(const char*);
    virtual bool r08(const char* s, int v);           // +0x20
    virtual bool r09(const char* fmt, ...);           // +0x24  (variadic)
    virtual bool r10(const char* name, const char* value); // +0x28
    virtual bool r11(const char* name, const char* fmt, ...); // +0x2c (variadic)
    virtual void r12();                               // +0x30
    virtual bool r13(const void* data, int n);        // +0x34
    virtual int  r14();                               // +0x38

    ReportWriter_s0091_e650();                                   // e970
    void GetFileNameExtension(char* dst, unsigned n);// e990 0x0091e990
    bool Open(const char* path);                      // e9c0
    bool Close();                                     // ea20
    bool BeginSection(const char* name);              // ea50 0x0091ea50
    void EndSection();                                // ea80 0x0091ea80
    bool WriteSubstr(const char* data, bool flag);    // ea90
    bool WriteFormattedV(const char* fmt, va_list ap);// ead0
    bool WritePair(const char* a, const char* b);     // eb20
    bool WriteFormatted(const char* name, const char* fmt, ...); // eba0 0x0091ead0
    bool NewLine();                                   // ebf0
    bool Write(const char* data, unsigned n);         // ec00 0x0091ec00
    long Tell();                                      // ec60
    void Seek(long off);                              // ec80
    int  GetTimeString(char* buf, unsigned n, void* tm); // eca0 0x0091eca0
    int  GetDateString(char* buf, unsigned n, void* tm); // ecf0 0x0091ecf0
    int  GetAddressLocation(void* addr, char* buf, unsigned n, int* a, int* b); // ed80 0x0091ed80
    int  GetAddressLocationString(void* addr, char* buf, unsigned n); // ee80 0x0091ee80
    bool WriteSystemInfo();                           // ef30 0x0091ef30
    bool WriteApplicationInfo();                      // f300 0x0091f300
    bool WriteDisassembly(void* start, unsigned n, void* eip); // f400 0x0091f400

    char mPath[256];      // +0x04
    void* mpFile;         // +0x104
    char mBuffer[1024];   // +0x108
    int mnSectionDepth;   // +0x508
};
struct ExceptionHandler_s0091_e650 {
    void* mpPlatformHandler;     // +0x00
    ReportWriter_s0091_e650** mpBegin;      // +0x04
    ReportWriter_s0091_e650** mpEnd;        // +0x08
    ReportWriter_s0091_e650** mpCapacity;   // +0x0c
    void* pad10;                 // +0x10
    ReportWriter_s0091_e650** mPoolBegin;   // +0x14
    void* pad18;                 // +0x18
    ReportWriter_s0091_e650* mInline[4];    // +0x1c
    bool mbRunningTrapped;       // +0x2c
    char pad2d[3];
    HandlerNode mNode;           // +0x30
    CString msBuildDescription;  // +0x3c
    wchar_t mDir[255];           // +0x4c
    ExceptionHandler_s0091_e650();                             // e810
    ~ExceptionHandler_s0091_e650();                            // e8d0
    void SetBuildDescription(const char* s);        // e650
    void NotifyClients(int action);                 // 91e3b0 (other slice) 0x0091e3b0
};
struct ExceptionHandlerWin32_s0091_e650 {
    ExceptionHandler_s0091_e650* mpOwner;   // +0x00
    ReportWriter_s0091_e650* mpReportWriter;// +0x04
    bool mbEnabled;              // +0x08
    char pad09[3];
    int mAction;                 // +0x0c
    int mnTerminateReturnValue;  // +0x10
    int mReportFieldMask;        // +0x14
    void* mpExceptionPointers;   // +0x18
    void* mpExceptionAddress;    // +0x1c
    void* mPreviousFilter;       // +0x20
    char mTime[0x24];            // +0x24
    char mBaseReportName[0x40];  // +0x48
    ExceptionHandlerWin32_s0091_e650(ExceptionHandler_s0091_e650* owner); // e770
    unsigned ExceptionFilter(void* ep);             // e690
    void WriteMiniDump();                           // 91e190 (other slice) 0x0091e190
    void WriteExceptionReport();                    // 91e5c0 (other slice) 0x0091e5c0
};
ExceptionHandlerWin32_s0091_e650* g_pExceptionHandler;   // 0x1667b7c
// ---- items of slice s0091e650 end

// @ 0x0091d950
void ExceptionHandlerWin32::GetExceptionString(char* buf, unsigned n)
{
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
void ExceptionHandlerWin32::WriteCallStack()
{
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
void Holder::Set(int a, int b)
{
    if (mpInner != 0) {
        struct Inner { char pad[0xc]; int f0c; int f10; };
        Inner* p = (Inner*)mpInner;
        p->f0c = a;
        p->f10 = b;
    }
}

// @ 0x0091e040
void ExceptionHandler::SetReportDirectory(wchar_t* dir)
{
    wcsncpy(mDir, dir, 0xff);
    mDir[254] = 0;
    EA_IO_EnsureTrailingPathSeparator(mDir, -1);
}

// @ 0x0091e080
int ExceptionHandlerWin32::GetReportFilePath(char* buf, unsigned n, int type)
{
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
void ExceptionHandlerWin32::WriteMiniDump()
{
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
void ExceptionHandlerWin32::WriteHeader()
{
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
void ExceptionHandler::NotifyClients(int action)
{
    HandlerNode* sentinel = &mNode;
    for (HandlerNode* n = sentinel->mpNext; n != sentinel; n = n->mpNext) {
        void** client = (void**)n->mClient;
        void** vt = (void**)*client;
        typedef void (__thiscall *Fn)(void*, ExceptionHandler*, int);
        ((Fn)vt[1])(client, this, action);
    }
}

// @ 0x0091e3e0
void ExceptionHandlerWin32::WriteExtraData()
{
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
void ExceptionHandlerWin32::WriteExceptionReportInternal(ReportWriter* w)
{
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
void ExceptionHandlerWin32::WriteExceptionReport()
{
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

// @ 0x0091e650
void ExceptionHandler_s0091_e650::SetBuildDescription(const char* s)
{
    if (s != 0) {
        msBuildDescription.assign(s, s + strlen(s));
    } else {
        if (msBuildDescription.mpBegin != msBuildDescription.mpEnd) {
            *msBuildDescription.mpBegin = 0;
            msBuildDescription.mpEnd = msBuildDescription.mpBegin;
        }
    }
}

// @ 0x0091e690
unsigned ExceptionHandlerWin32_s0091_e650::ExceptionFilter(void* ep)
{
    mpExceptionPointers = ep;
    mpExceptionAddress = *(void**)(*(char**)ep + 0xc);
    __int64 t = _time64(0);
    void* lt = _localtime64(&t);
    void* prev = mPreviousFilter;
    memcpy(mTime, lt, 0x24);
    prev = SetUnhandledExceptionFilter(prev);
    if (mpOwner != 0)
        mpOwner->NotifyClients(0);
    if (mReportFieldMask != 0)
        WriteExceptionReport();
    WriteMiniDump();
    if (mpOwner != 0)
        mpOwner->NotifyClients(1);
    SetUnhandledExceptionFilter(prev);
    if (mAction == 1) {
        UINT code = (UINT)mnTerminateReturnValue;
        TerminateProcess(GetCurrentProcess(), code);
        return (unsigned)mnTerminateReturnValue;
    }
    return mAction != 2;
}

// @ 0x0091e750
extern "C" unsigned __stdcall ExceptionFilterThunk(void* ep)
{
    if (g_pExceptionHandler == 0)
        return 0;
    return g_pExceptionHandler->ExceptionFilter(ep);
}

// @ 0x0091e770
ExceptionHandlerWin32_s0091_e650::ExceptionHandlerWin32_s0091_e650(ExceptionHandler_s0091_e650* owner)
{
    mpOwner = owner;
    mbEnabled = false;
    mpReportWriter = 0;
    mAction = 0;
    mpExceptionPointers = 0;
    mpExceptionAddress = 0;
    mPreviousFilter = 0;
    mnTerminateReturnValue = -1;
    mReportFieldMask = -1;
    memset(mTime, 0, 0x24);
    g_pExceptionHandler = this;
    strncpy(mBaseReportName, "Exception Report", 0x11);
    if (mbEnabled == false) {
        mbEnabled = true;
        mPreviousFilter = SetUnhandledExceptionFilter((void*)ExceptionFilterThunk);
    }
}

// @ 0x0091e810
ExceptionHandler_s0091_e650::ExceptionHandler_s0091_e650()
{
    mpPlatformHandler = 0;
    ReportWriter_s0091_e650** p = (ReportWriter_s0091_e650**)&mInline[0];
    mPoolBegin = p;
    mpEnd = p;
    mpBegin = p;
    mpCapacity = p + 4;
    mbRunningTrapped = false;
    mNode.mpNext = &mNode;
    mNode.mpPrev = &mNode;
    msBuildDescription.mpBegin = (char*)0x1667bac;
    msBuildDescription.mpEnd = (char*)0x1667bac;
    msBuildDescription.mpCapacity = (char*)0x1667bad;
    mDir[0] = 0;
    ReportWriter_s0091_e650** src = mpEnd;
    ReportWriter_s0091_e650** dst = mpBegin;
    DoInsertValue(dst, src, (unsigned)(src - src));
    mpEnd -= (src - dst);
    if (mpPlatformHandler == 0) {
        void* mem = EASTL_allocator_allocate(0x88, "ExceptionHandlerWin32", 0, 0, 0, 0);
        if (mem != 0) {
            ExceptionHandlerWin32_s0091_e650* w = new (mem) ExceptionHandlerWin32_s0091_e650(this);
            mpPlatformHandler = w;
        } else {
            mpPlatformHandler = 0;
        }
        NotifyClients(2);
    }
}

// @ 0x0091e970
ReportWriter_s0091_e650::ReportWriter_s0091_e650()
{
    mpFile = 0;
    mnSectionDepth = 0;
    mPath[0] = 0;
}
