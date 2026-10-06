// Slice s0091e650: EA::Debug ReportWriter (file/string/format helpers, system &
// application info, disassembly) and the ExceptionHandler/Win32 lifecycle.
#include "types.h"
#include <stdarg.h>

typedef unsigned int size_t;

// ---------------------------------------------------------------- win32 types
typedef void* HANDLE;
typedef void* HMODULE;
typedef void* HLOCAL;
typedef void* FILEP;
typedef unsigned long DWORD;
typedef int BOOL;
typedef const char* LPCSTR;
typedef char* LPSTR;
typedef unsigned int UINT;
typedef unsigned long SIZE_T;
typedef long LONG;

struct MEMORY_BASIC_INFORMATION {
    void* BaseAddress; void* AllocationBase; DWORD AllocationProtect;
    DWORD RegionSize; DWORD State; DWORD Protect; DWORD Type;
};
struct SYSTEM_INFO {
    unsigned short wProcessorArchitecture; unsigned short wReserved;
    DWORD dwPageSize; void* lpMinimumApplicationAddress; void* lpMaximumApplicationAddress;
    DWORD dwActiveProcessorMask; DWORD dwNumberOfProcessors; DWORD dwProcessorType;
    DWORD dwAllocationGranularity; unsigned short wProcessorLevel; unsigned short wProcessorRevision;
};
struct OSVERSIONINFOA {
    DWORD dwOSVersionInfoSize; DWORD dwMajorVersion; DWORD dwMinorVersion;
    DWORD dwBuildNumber; DWORD dwPlatformId; char szCSDVersion[128];
};
struct MEMORYSTATUSEX {
    DWORD dwLength; DWORD dwMemoryLoad; unsigned __int64 ullTotalPhys; unsigned __int64 ullAvailPhys;
    unsigned __int64 ullTotalPageFile; unsigned __int64 ullAvailPageFile;
    unsigned __int64 ullTotalVirtual; unsigned __int64 ullAvailVirtual; unsigned __int64 ullAvailExtendedVirtual;
};
struct VS_FIXEDFILEINFO {
    DWORD dwSignature; DWORD dwStrucVersion; DWORD dwFileVersionMS; DWORD dwFileVersionLS;
    DWORD dwProductVersionMS; DWORD dwProductVersionLS; DWORD dwFileFlagsMask; DWORD dwFileFlags;
    DWORD dwFileOS; DWORD dwFileType; DWORD dwFileSubtype; DWORD dwFileDateMS; DWORD dwFileDateLS;
};

// imports
extern "C" __declspec(dllimport) void* __cdecl memcpy(void*, const void*, size_t);
extern "C" __declspec(dllimport) void* __cdecl memset(void*, int, size_t);
extern "C" __declspec(dllimport) char* __cdecl strncpy(char*, const char*, size_t);
inline void* operator new(unsigned int, void* p) { return p; }
extern "C" __declspec(dllimport) size_t __cdecl strlen(const char*);
extern "C" __declspec(dllimport) FILEP __cdecl fopen(const char*, const char*);
extern "C" __declspec(dllimport) int __cdecl fclose(FILEP);
extern "C" __declspec(dllimport) size_t __cdecl fwrite(const void*, size_t, size_t, FILEP);
extern "C" __declspec(dllimport) int __cdecl fflush(FILEP);
extern "C" __declspec(dllimport) long __cdecl ftell(FILEP);
extern "C" __declspec(dllimport) int __cdecl fseek(FILEP, long, int);
extern "C" __declspec(dllimport) int __cdecl _vsnprintf(char*, size_t, const char*, va_list);
extern "C" __declspec(dllimport) int __cdecl _snprintf(char*, size_t, const char*, ...);
extern "C" __declspec(dllimport) int __cdecl sprintf(char*, const char*, ...);
extern "C" __declspec(dllimport) size_t __cdecl strftime(char*, size_t, const char*, const void*);
extern "C" __declspec(dllimport) __int64 __cdecl _time64(__int64*);
extern "C" __declspec(dllimport) void* __cdecl _localtime64(const __int64*);

extern "C" __declspec(dllimport) DWORD __stdcall GetComputerNameA(char*, DWORD*);
extern "C" __declspec(dllimport) BOOL __stdcall GetUserNameA(char*, DWORD*);
extern "C" __declspec(dllimport) BOOL __stdcall GetComputerNameExA(int, char*, DWORD*);
extern "C" __declspec(dllimport) BOOL __stdcall GetVersionExA(OSVERSIONINFOA*);
extern "C" __declspec(dllimport) void __stdcall GetSystemInfo(SYSTEM_INFO*);
extern "C" __declspec(dllimport) BOOL __stdcall IsDebuggerPresent();
extern "C" __declspec(dllimport) BOOL __stdcall GlobalMemoryStatusEx(MEMORYSTATUSEX*);
extern "C" __declspec(dllimport) SIZE_T __stdcall VirtualQuery(const void*, MEMORY_BASIC_INFORMATION*, SIZE_T);
extern "C" __declspec(dllimport) DWORD __stdcall GetModuleFileNameA(HMODULE, char*, DWORD);
extern "C" __declspec(dllimport) void* __stdcall SetUnhandledExceptionFilter(void*);
extern "C" __declspec(dllimport) HANDLE __stdcall GetCurrentProcess();
extern "C" __declspec(dllimport) BOOL __stdcall TerminateProcess(HANDLE, UINT);
extern "C" __declspec(dllimport) HLOCAL __stdcall LocalAlloc(UINT, SIZE_T);
extern "C" __declspec(dllimport) HLOCAL __stdcall LocalFree(HLOCAL);
extern "C" __declspec(dllimport) DWORD __stdcall GetFileVersionInfoSizeA(LPCSTR, DWORD*);
extern "C" __declspec(dllimport) BOOL __stdcall GetFileVersionInfoA(LPCSTR, DWORD, DWORD, void*);
extern "C" __declspec(dllimport) BOOL __stdcall VerQueryValueA(const void*, LPCSTR, void**, UINT*);

void* EASTL_allocator_allocate(uint32_t n, const char* name, int flags, unsigned dbg,
                               const char* file, int line);   // 0x00f473a0
void  EASTL_allocator_deallocate(void* p);                     // 0x00f47380
void  DoInsertValue(void* dst, const void* src, unsigned n);   // 0x011e0744
void* vec_new(unsigned n, int def, void* a);                   // 0x011e073e  operator_new[]
struct DisassemblerX86 {
    DisassemblerX86();                                          // 0x0091b5d0
    ~DisassemblerX86();                                         // 0x0091b6b0
    unsigned Dasm(unsigned a, unsigned b, void* c, int d, unsigned e, unsigned f); // 0x91b6d0
};

// ---------------------------------------------------------------- structs
struct CString {
    char* mpBegin; char* mpEnd; char* mpCapacity;
    void assign(const char* first, const char* last);          // 0x00454cb0
};

struct HandlerNode { HandlerNode* mpNext; HandlerNode* mpPrev; void* mClient; };

struct ReportWriter {
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

    ReportWriter();                                   // e970
    void GetFileNameExtension(char* dst, unsigned n);// e990
    bool Open(const char* path);                      // e9c0
    bool Close();                                     // ea20
    bool BeginSection(const char* name);              // ea50
    void EndSection();                                // ea80
    bool WriteSubstr(const char* data, bool flag);    // ea90
    bool WriteFormattedV(const char* fmt, va_list ap);// ead0
    bool WritePair(const char* a, const char* b);     // eb20
    bool WriteFormatted(const char* name, const char* fmt, ...); // eba0
    bool NewLine();                                   // ebf0
    bool Write(const char* data, unsigned n);         // ec00
    long Tell();                                      // ec60
    void Seek(long off);                              // ec80
    int  GetTimeString(char* buf, unsigned n, void* tm); // eca0
    int  GetDateString(char* buf, unsigned n, void* tm); // ecf0
    int  GetAddressLocation(void* addr, char* buf, unsigned n, int* a, int* b); // ed80
    int  GetAddressLocationString(void* addr, char* buf, unsigned n); // ee80
    bool WriteSystemInfo();                           // ef30
    bool WriteApplicationInfo();                      // f300
    bool WriteDisassembly(void* start, unsigned n, void* eip); // f400

    char mPath[256];      // +0x04
    void* mpFile;         // +0x104
    char mBuffer[1024];   // +0x108
    int mnSectionDepth;   // +0x508
};

struct ExceptionHandler {
    void* mpPlatformHandler;     // +0x00
    ReportWriter** mpBegin;      // +0x04
    ReportWriter** mpEnd;        // +0x08
    ReportWriter** mpCapacity;   // +0x0c
    void* pad10;                 // +0x10
    ReportWriter** mPoolBegin;   // +0x14
    void* pad18;                 // +0x18
    ReportWriter* mInline[4];    // +0x1c
    bool mbRunningTrapped;       // +0x2c
    char pad2d[3];
    HandlerNode mNode;           // +0x30
    CString msBuildDescription;  // +0x3c
    wchar_t mDir[255];           // +0x4c
    ExceptionHandler();                             // e810
    ~ExceptionHandler();                            // e8d0
    void SetBuildDescription(const char* s);        // e650
    void NotifyClients(int action);                 // 91e3b0 (other slice)
};

struct ExceptionHandlerWin32 {
    ExceptionHandler* mpOwner;   // +0x00
    ReportWriter* mpReportWriter;// +0x04
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
    ExceptionHandlerWin32(ExceptionHandler* owner); // e770
    unsigned ExceptionFilter(void* ep);             // e690
    void WriteMiniDump();                           // 91e190 (other slice)
    void WriteExceptionReport();                    // 91e5c0 (other slice)
};

ExceptionHandlerWin32* g_pExceptionHandler;   // 0x1667b7c

// ---------------------------------------------------------------- bodies
// @ 0x0091e650
void ExceptionHandler::SetBuildDescription(const char* s) {
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
unsigned ExceptionHandlerWin32::ExceptionFilter(void* ep) {
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
extern "C" unsigned __stdcall ExceptionFilterThunk(void* ep) {
    if (g_pExceptionHandler == 0)
        return 0;
    return g_pExceptionHandler->ExceptionFilter(ep);
}

// @ 0x0091e770
ExceptionHandlerWin32::ExceptionHandlerWin32(ExceptionHandler* owner) {
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
ExceptionHandler::ExceptionHandler() {
    mpPlatformHandler = 0;
    ReportWriter** p = (ReportWriter**)&mInline[0];
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
    ReportWriter** src = mpEnd;
    ReportWriter** dst = mpBegin;
    DoInsertValue(dst, src, (unsigned)(src - src));
    mpEnd -= (src - dst);
    if (mpPlatformHandler == 0) {
        void* mem = EASTL_allocator_allocate(0x88, "ExceptionHandlerWin32", 0, 0, 0, 0);
        if (mem != 0) {
            ExceptionHandlerWin32* w = new (mem) ExceptionHandlerWin32(this);
            mpPlatformHandler = w;
        } else {
            mpPlatformHandler = 0;
        }
        NotifyClients(2);
    }
}

// @ 0x0091e8d0
ExceptionHandler::~ExceptionHandler() {
    if (mpPlatformHandler != 0 && !mbRunningTrapped) {
        NotifyClients(3);
        ExceptionHandlerWin32* w = (ExceptionHandlerWin32*)mpPlatformHandler;
        if (w != 0) {
            g_pExceptionHandler = 0;
            if (w->mbEnabled) {
                w->mbEnabled = false;
                SetUnhandledExceptionFilter(w->mPreviousFilter);
                w->mPreviousFilter = 0;
            }
            EASTL_allocator_deallocate(w);
        }
        mpPlatformHandler = 0;
    }
    char* b = msBuildDescription.mpBegin;
    if ((int)(msBuildDescription.mpCapacity - b) > 1 && b != 0)
        EASTL_allocator_deallocate(b);
    HandlerNode* sentinel = &mNode;
    for (HandlerNode* n = sentinel->mpNext; n != sentinel; ) {
        HandlerNode* nx = n->mpNext;
        EASTL_allocator_deallocate(n);
        n = nx;
    }
    if (mpBegin != 0 && mpBegin != mPoolBegin)
        EASTL_allocator_deallocate(mpBegin);
}

// @ 0x0091e970
ReportWriter::ReportWriter() {
    mpFile = 0;
    mnSectionDepth = 0;
    mPath[0] = 0;
}

// @ 0x0091e990
void ReportWriter::GetFileNameExtension(char* dst, unsigned n) {
    strncpy(dst, ".txt", n);
    dst[n - 1] = 0;
}

// @ 0x0091e9c0
bool ReportWriter::Open(const char* path) {
    if (mpFile == 0) {
        if (path != 0) {
            strncpy(mPath, path, 0x100);
            mPath[0xff] = 0;
        }
        mpFile = fopen(mPath, "wb");
        return mpFile != 0;
    }
    return false;
}

// @ 0x0091ea20
bool ReportWriter::Close() {
    if (mpFile != 0)
        fclose((FILEP)mpFile);
    return mpFile != 0;
}

// @ 0x0091ea50
bool ReportWriter::BeginSection(const char* name) {
    ++mnSectionDepth;
    if (mnSectionDepth == 1)
        return r09("[%s]\r\n", name);
    return false;
}

// @ 0x0091ea80
void ReportWriter::EndSection() {
    --mnSectionDepth;
    r12();
}

// @ 0x0091ea90
bool ReportWriter::WriteSubstr(const char* data, bool flag) {
    if (!r13(data, -1))
        return false;
    if (flag)
        return r13("\r\n", 2);
    return true;
}

// @ 0x0091ead0
bool ReportWriter::WriteFormattedV(const char* fmt, va_list ap) {
    int n = _vsnprintf(mBuffer, 0x400, fmt, ap);
    if ((unsigned)(n - 1) < 0x3ff)
        return r13(mBuffer, n);
    return false;
}

// @ 0x0091eb20
bool ReportWriter::WritePair(const char* a, const char* b) {
    if (!r13(a, (int)strlen(a)))
        return false;
    if (!r13(": ", 2))
        return false;
    if (!r13(b, (int)strlen(b)))
        return false;
    if (!r13("\r\n", 2))
        return false;
    return true;
}

// @ 0x0091eba0
bool ReportWriter::WriteFormatted(const char* name, const char* fmt, ...) {
    va_list ap;
    va_start(ap, fmt);
    int n = _vsnprintf(mBuffer, 0x400, fmt, ap);
    va_end(ap);
    unsigned x = (unsigned)(n - 1);
    if (x > 0x3fe)
        return false;
    return r10(name, mBuffer);
}

// @ 0x0091ebf0
bool ReportWriter::NewLine() {
    return r13("\r\n", 2);
}

// @ 0x0091ec00
bool ReportWriter::Write(const char* data, unsigned n) {
    if (mpFile != 0) {
        if (n > 0xf4240)
            n = (unsigned)strlen(data);
        size_t w = fwrite(data, 1, n, (FILEP)mpFile);
        fflush((FILEP)mpFile);
        return w == n;
    }
    return false;
}

// @ 0x0091ec60
long ReportWriter::Tell() {
    if (mpFile != 0)
        return ftell((FILEP)mpFile);
    return 0;
}

// @ 0x0091ec80
void ReportWriter::Seek(long off) {
    if (mpFile != 0)
        fseek((FILEP)mpFile, off, 0);
}

// @ 0x0091eca0
int ReportWriter::GetTimeString(char* buf, unsigned n, void* tm) {
    if (tm == 0) {
        __int64 t = _time64(0);
        tm = _localtime64(&t);
    }
    return (int)strftime(buf, n, "%H.%M.%S", tm);
}

// @ 0x0091ecf0
int ReportWriter::GetDateString(char* buf, unsigned n, void* tm) {
    if (tm == 0) {
        __int64 t = _time64(0);
        tm = _localtime64(&t);
    }
    return (int)strftime(buf, n, "%m-%d-%y", tm);
}

// @ 0x0091ed40
int __stdcall GetComputerNameHelper(char* buf, unsigned n) {
    *buf = 0;
    unsigned sz = n;
    if (!GetComputerNameA(buf, (DWORD*)&sz))
        *buf = 0;
    return (int)strlen(buf);
}

// @ 0x0091ed80
int ReportWriter::GetAddressLocation(void* addr, char* buf, unsigned n, int* a, int* b) {
    buf[0] = 0;
    MEMORY_BASIC_INFORMATION mbi;
    if (VirtualQuery(addr, &mbi, 0x1c) == 0)
        return 0;
    char fname[512];
    fname[0] = 0;
    if (mbi.AllocationBase == 0)
        return 0;
    if (GetModuleFileNameA((HMODULE)mbi.AllocationBase, fname, 0x1ff) == 0)
        return 0;
    // walk the PE export directory looking for the section containing addr
    char* base = (char*)mbi.AllocationBase;
    unsigned peOff = *(unsigned*)(base + 0x3c);
    unsigned numSections = *(unsigned short*)(base + peOff + 6);
    unsigned optOff = peOff + 0x18;
    unsigned sizeOpt = *(unsigned short*)(base + peOff + 0x14);
    unsigned secOff = optOff + sizeOpt;
    unsigned rva = (unsigned)((char*)addr - base);
    for (unsigned i = 0; i < numSections; ++i) {
        char* sec = base + secOff + i * 0x28;
        unsigned va = *(unsigned*)(sec + 0xc);
        unsigned vsize = *(unsigned*)(sec + 8) + va;
        if (rva >= va && rva < vsize) {
            strncpy(buf, fname, n);
            buf[n - 1] = 0;
            *a = i + 1;
            *b = 0;
            return (int)strlen(buf);
        }
    }
    return 0;
}

// @ 0x0091ee80
int ReportWriter::GetAddressLocationString(void* addr, char* buf, unsigned n) {
    int a = 0, b = 0;
    char loc[384];
    if (GetAddressLocation(addr, loc, 0x180, &a, &b) != 0) {
        _snprintf(buf, n, "0x%08x \"%s\":0x%04x:0x%08x", (unsigned)addr, loc, a, b);
        return 1;
    }
    _snprintf(buf, n, "0x%08x <unknown module>", (unsigned)addr);
    return 1;
}

// @ 0x0091ef30
bool ReportWriter::WriteSystemInfo() {
    char buf[0x100];
    DWORD sz = 0x100;
    if (GetComputerNameExA(3, buf, &sz) > 0)
        r10("Computer name", buf);
    sz = 0x100;
    if (GetUserNameA(buf, &sz) > 0)
        r10("User name", buf);
    r10("EA_PLATFORM", "Windows on X86");

    OSVERSIONINFOA os;
    os.dwOSVersionInfoSize = 0x9c;
    if (GetVersionExA(&os)) {
        const char* osname = "Windows 98 or earlier";
        if (os.dwMajorVersion >= 6) osname = "Windows Vista";
        else if (os.dwMajorVersion == 5) {
            if (os.dwMinorVersion == 0) osname = "Windows 2000";
            else if (os.dwMinorVersion == 1) osname = "Windows XP";
            else osname = "Windows Server 2003";
        }
        r10("OS name", osname);
        char ver[64];
        sprintf(ver, "%u.%u.%u", os.dwMajorVersion, os.dwMinorVersion, os.dwBuildNumber);
        r10("OS version number", ver);
        r10("OS service pack", os.szCSDVersion);
    }
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    const char* dbg = IsDebuggerPresent() ? "yes" : "no";
    r10("Debugger present", dbg);
    char num[64];
    sprintf(num, "%u", si.dwNumberOfProcessors);
    r10("CPU count", num);
    const char* cpu = "x86 on x86-64";
    if (si.wProcessorArchitecture == 0) cpu = "x86";
    else if (si.wProcessorArchitecture == 9) cpu = "x86-64";
    r10("Processor type", cpu);
    sprintf(num, "%u", si.wProcessorLevel);
    r10("Processor level", num);
    sprintf(num, "%u", si.wProcessorRevision);
    r10("Processor revision", num);

    MEMORYSTATUSEX ms;
    ms.dwLength = 0x40;
    if (GlobalMemoryStatusEx(&ms)) {
        sprintf(num, "%d%%", ms.dwMemoryLoad);
        r10("Memory load", num);
        sprintf(num, "%I64d Mb", ms.ullTotalPhys >> 20);
        r10("Total physical memory", num);
        sprintf(num, "%I64d Mb", ms.ullAvailPhys >> 20);
        r10("Available physical memory", num);
        sprintf(num, "%I64d Mb", ms.ullTotalPageFile >> 20);
        r10("Total page file memory", num);
        sprintf(num, "%I64d Mb", ms.ullAvailPageFile >> 20);
        r10("Available page file memory", num);
        sprintf(num, "%I64d Mb", ms.ullTotalVirtual >> 20);
        r10("Total virtual memory", num);
        sprintf(num, "%I64d Mb", ms.ullAvailVirtual >> 20);
        r10("Free virtual memory", num);
    }
    return true;
}

// @ 0x0091f300
bool ReportWriter::WriteApplicationInfo() {
    r10("Language", "C++");
    r10("Compiler", "Microsoft Visual C++ compiler, version 1500");
    char path[0x104];
    DWORD n = GetModuleFileNameA(0, path, 0x104);
    if (n != 0 && n < 0x104)
        r10("App path", path);

    DWORD dummy = 0;
    DWORD sz = GetFileVersionInfoSizeA(path, &dummy);
    if (sz != 0) {
        HLOCAL data = LocalAlloc(0x40, sz);
        if (data != 0) {
            if (GetFileVersionInfoA(path, 0, sz, data)) {
                void* vi = 0;
                UINT len = 0;
                if (VerQueryValueA(data, "\\", &vi, &len)) {
                    unsigned short* p = (unsigned short*)vi;
                    r11("App version", "%u.%u.%u.%u",
                        p[5], p[4], p[7], p[6]);
                }
            }
            LocalFree(data);
        }
    }
    return false;
}

// @ 0x0091f400
bool ReportWriter::WriteDisassembly(void* start, unsigned n, void* eip) {
    DisassemblerX86 dis;
    char text[17];
    char bytes[32];
    char tail[447];
    unsigned cur = (unsigned)start;
    unsigned end = (unsigned)start + n;
    while (cur != end) {
        unsigned next = dis.Dasm(cur, end, text, 3, cur, 0);
        const char* fmt;
        if (eip == 0 || next <= (unsigned)eip) {
            fmt = "%s    %s %s\r\n";
        } else {
            eip = 0;
            fmt = "%s => %s %s\r\n";
        }
        _snprintf(mBuffer, 0x400, fmt, text, bytes, tail);
        r08(mBuffer, 0);
        cur = next;
    }
    return true;
}
