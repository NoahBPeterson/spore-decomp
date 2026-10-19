// src/game/UTFSpore_Win32/ReportWriter.cpp -- migrated from slice(s) s0091f520, s0091e650 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/ReportWriter.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Debug/ReportWriter.h"
#include <stdarg.h>
#include "EA/Dasm/DisassemblerX86.h"
#include <string.h>

// ---- items of slice s0091e650 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef void* HMODULE;
typedef void* HLOCAL;
typedef void* FILEP;
typedef unsigned long DWORD;
typedef int BOOL;
typedef const char* LPCSTR;
typedef unsigned int UINT;
typedef unsigned long SIZE_T;
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
extern "C" __declspec(dllimport) size_t __cdecl strlen(const char*);
extern "C" __declspec(dllimport) int __cdecl _snprintf(char*, size_t, const char*, ...);
extern "C" __declspec(dllimport) DWORD __stdcall GetComputerNameA(char*, DWORD*);
struct DisassemblerX86 {
    DisassemblerX86();                                          // 0x0091b5d0
    ~DisassemblerX86();                                         // 0x0091b6b0
    unsigned Dasm(unsigned a, unsigned b, void* c, int d, unsigned e, unsigned f); // 0x91b6d0
};
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
extern "C" __declspec(dllimport) char* __cdecl strncpy(char*, const char*, size_t);
extern "C" __declspec(dllimport) FILEP __cdecl fopen(const char*, const char*);
extern "C" __declspec(dllimport) int __cdecl fclose(FILEP);
extern "C" __declspec(dllimport) size_t __cdecl fwrite(const void*, size_t, size_t, FILEP);
extern "C" __declspec(dllimport) int __cdecl fflush(FILEP);
extern "C" __declspec(dllimport) long __cdecl ftell(FILEP);
extern "C" __declspec(dllimport) int __cdecl fseek(FILEP, long, int);
extern "C" __declspec(dllimport) int __cdecl _vsnprintf(char*, size_t, const char*, va_list);
extern "C" __declspec(dllimport) int __cdecl sprintf(char*, const char*, ...);
extern "C" __declspec(dllimport) size_t __cdecl strftime(char*, size_t, const char*, const void*);
extern "C" __declspec(dllimport) __int64 __cdecl _time64(__int64*);
extern "C" __declspec(dllimport) void* __cdecl _localtime64(const __int64*);
extern "C" __declspec(dllimport) BOOL __stdcall GetUserNameA(char*, DWORD*);
extern "C" __declspec(dllimport) BOOL __stdcall GetComputerNameExA(int, char*, DWORD*);
extern "C" __declspec(dllimport) BOOL __stdcall GetVersionExA(OSVERSIONINFOA*);
extern "C" __declspec(dllimport) void __stdcall GetSystemInfo(SYSTEM_INFO*);
extern "C" __declspec(dllimport) BOOL __stdcall IsDebuggerPresent();
extern "C" __declspec(dllimport) BOOL __stdcall GlobalMemoryStatusEx(MEMORYSTATUSEX*);
extern "C" __declspec(dllimport) DWORD __stdcall GetModuleFileNameA(HMODULE, char*, DWORD);
extern "C" __declspec(dllimport) HLOCAL __stdcall LocalAlloc(UINT, SIZE_T);
extern "C" __declspec(dllimport) HLOCAL __stdcall LocalFree(HLOCAL);
extern "C" __declspec(dllimport) DWORD __stdcall GetFileVersionInfoSizeA(LPCSTR, DWORD*);
extern "C" __declspec(dllimport) BOOL __stdcall GetFileVersionInfoA(LPCSTR, DWORD, DWORD, void*);
extern "C" __declspec(dllimport) BOOL __stdcall VerQueryValueA(const void*, LPCSTR, void**, UINT*);
// ---- items of slice s0091e650 end

// ---- items of slice s0091f520 begin (TODO(rewrite): local stubs, replace by canonical classes)
extern "C" __declspec(dllimport) void* __stdcall LoadLibraryA(const char*);
extern "C" __declspec(dllimport) void* __stdcall GetProcAddress(void*, const char*);
extern "C" __declspec(dllimport) void* __stdcall GetCurrentProcess();
#pragma intrinsic(__readfsdword)
unsigned long __cdecl __readfsdword(unsigned);
struct MODULEINFO {
    void*    lpBaseOfDll;   // +0
    uint32_t SizeOfImage;   // +4
    void*    EntryPoint;    // +8
};
struct ReportWriter_s0091_f520 {
    virtual void v00();                              // 0x00
    virtual void v04();                              // 0x04
    virtual int  v08(int, int);                      // 0x08
    virtual int  v0c(int);                           // 0x0c
    virtual int  v10(int, int*);                     // 0x10
    virtual int  v14(int);                           // 0x14
    virtual void v18(const char*);                   // 0x18
    virtual void v1c(const char*);                   // 0x1c
    virtual void v20(const char*, int);              // 0x20
    virtual void v24(const char*, ...);              // 0x24 (variadic -> cdecl, this first)
    virtual void v28(const char*, const char*);      // 0x28
    virtual void v2c();                              // 0x2c
    virtual int  v30();                              // 0x30
    virtual void v34(const char*, int);              // 0x34

    bool WriteMemoryView(uint8_t* base, int len, uint8_t* mark, const char* label); // 0x0091f520
    bool WriteStackMemoryView(unsigned lo, int len);                                 // 0x0091fe60
    bool WriteRegisterMemoryView(int* ctx);                                          // 0x0091fbd0
    bool WriteRegisterValues(int* ctx);                                              // 0x0091fa10
    bool WriteModuleList();                                                          // 0x0091f7c0
    bool WriteCallStack(int* ctx);                                                   // 0x0091fca0
};
static inline unsigned CStrLen(const char* s)
{
    const char* e = s + 1;
    char c;
    do { c = *s; ++s; } while (c != 0);
    return (unsigned)(s - e);
}
typedef int (__stdcall *EnumProcessModules_t)(void*, void**, unsigned, unsigned*);
typedef int (__stdcall *GetModuleFileNameExA_t)(void*, void*, char*, unsigned);
typedef int (__stdcall *GetModuleBaseNameA_t)(void*, void*, char*, unsigned);
typedef int (__stdcall *GetModuleInformation_t)(void*, void*, void*, unsigned);
static inline void AppendQuote(char* s)
{
    // terminate one past the end, then put the closing quote over the old terminator
    unsigned n1 = CStrLen(s);
    s[n1 + 1] = 0;
    unsigned n2 = CStrLen(s);
    s[n2] = '"';
}
struct AddressRepCache {                              // EA::Callstack::AddressRepCache (0x44 bytes)
    uint32_t d[0x11];
    void Init();                                      // 0x0091b2f0
    void Shutdown();                                  // 0x0091b090
    unsigned GetRep(int kind, uint32_t addr, void* a, void* b, int flag);   // 0x0091b0f0 (ret 0x14)
};
extern "C" unsigned __cdecl CS_GetCallstack(uint32_t*, int, void*); // 0x0091b3d0
extern "C" AddressRepCache* __cdecl CS_a1c0();                      // 0x0091a1c0
extern "C" void __cdecl CS_b580(uint32_t, char*, int);              // 0x0091b580
// ---- items of slice s0091f520 end

// @ 0x0091e990
void EA::Debug::ReportWriter::GetFileNameExtension(char * dst, unsigned int n)
{
    strncpy(dst, ".txt", n);
    dst[n - 1] = 0;
}

// @ 0x0091e9c0
bool EA::Debug::ReportWriter::OpenReport(char const * path)
{
    if (mpFile == 0) {
        if (path != 0) {
            strncpy(mPath, path, 0x100);
            mPath[0xff] = 0;
        }
        mpFile = (_iobuf*)fopen(mPath, "wb");
        return mpFile != 0;
    }
    return false;
}

// @ 0x0091ea20
bool EA::Debug::ReportWriter::CloseReport()
{
    if (mpFile != 0)
        fclose((FILEP)mpFile);
    return mpFile != 0;
}

// @ 0x0091ea50
bool EA::Debug::ReportWriter::BeginSection(char const * name)
{
    ++mnSectionDepth;
    if (mnSectionDepth == 1)
        return WriteFormatted("[%s]\r\n", name);
    return false;
}

// @ 0x0091ea80
bool EA::Debug::ReportWriter::EndSection(char const * a1)
{
    --mnSectionDepth;
    return WriteBlankLine();
}

// @ 0x0091ea90
bool EA::Debug::ReportWriter::WriteText(char const * data, bool flag)
{
    if (!Write(data, -1))
        return false;
    if (flag)
        return Write("\r\n", 2);
    return true;
}

// @ 0x0091ead0
bool EA::Debug::ReportWriter::WriteFormatted(char const * fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    int n = _vsnprintf(mBuffer, 0x400, fmt, ap);
    if ((unsigned)(n - 1) < 0x3ff)
        return Write(mBuffer, n);
    return false;
}

// @ 0x0091eb20
bool EA::Debug::ReportWriter::WriteKeyValue(char const * a, char const * b)
{
    if (!Write(a, strlen(a)))
        return false;
    if (!Write(": ", 2))
        return false;
    if (!Write(b, strlen(b)))
        return false;
    if (!Write("\r\n", 2))
        return false;
    return true;
}

// @ 0x0091eba0
bool EA::Debug::ReportWriter::WriteKeyValueFormatted(char const * name, char const * fmt, ...)
{
    va_list ap;
    va_start(ap, fmt);
    int n = _vsnprintf(mBuffer, 0x400, fmt, ap);
    va_end(ap);
    unsigned x = (unsigned)(n - 1);
    if (x > 0x3fe)
        return false;
    return WriteKeyValue(name, mBuffer);
}

// @ 0x0091ebf0
bool EA::Debug::ReportWriter::WriteBlankLine()
{
    return Write("\r\n", 2);
}

// @ 0x0091ec00
bool EA::Debug::ReportWriter::Write(char const * data, unsigned int n)
{
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
unsigned int EA::Debug::ReportWriter::GetPosition()
{
    if (mpFile != 0)
        return ftell((FILEP)mpFile);
    return 0;
}

// @ 0x0091ec80
void EA::Debug::ReportWriter::SetPosition(unsigned int off)
{
    if (mpFile != 0)
        fseek((FILEP)mpFile, off, 0);
}

// @ 0x0091eca0
unsigned int EA::Debug::ReportWriter::GetTimeString(char * buf, unsigned int n, tm const * tm) const
{
    if (tm == 0) {
        __int64 t = _time64(0);
        tm = (struct tm const *)_localtime64(&t);
    }
    return (int)strftime(buf, n, "%H.%M.%S", tm);
}

// @ 0x0091ecf0
unsigned int EA::Debug::ReportWriter::GetDateString(char * buf, unsigned int n, tm const * tm) const
{
    if (tm == 0) {
        __int64 t = _time64(0);
        tm = (struct tm const *)_localtime64(&t);
    }
    return (int)strftime(buf, n, "%m-%d-%y", tm);
}

// @ 0x0091ed40
int __stdcall GetComputerNameHelper(char* buf, unsigned n)
{
    *buf = 0;
    unsigned sz = n;
    if (!GetComputerNameA(buf, (DWORD*)&sz))
        *buf = 0;
    return (int)strlen(buf);
}

// @ 0x0091ee80
unsigned int EA::Debug::ReportWriter::GetAddressLocationString(void const * addr, char * buf, unsigned int n)
{
    unsigned int a = 0, b = 0;
    char loc[384];
    if (GetAddressLocation(addr, loc, 0x180, a, b) != 0) {
        _snprintf(buf, n, "0x%08x \"%s\":0x%04x:0x%08x", (unsigned)addr, loc, a, b);
        return 1;
    }
    _snprintf(buf, n, "0x%08x <unknown module>", (unsigned)addr);
    return 1;
}

// @ 0x0091ef30
bool EA::Debug::ReportWriter::WriteSystemInfo()
{
    char buf[0x100];
    DWORD sz = 0x100;
    if (GetComputerNameExA(3, buf, &sz) > 0)
        WriteKeyValue("Computer name", buf);
    sz = 0x100;
    if (GetUserNameA(buf, &sz) > 0)
        WriteKeyValue("User name", buf);
    WriteKeyValue("EA_PLATFORM", "Windows on X86");

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
        WriteKeyValue("OS name", osname);
        char ver[64];
        sprintf(ver, "%u.%u.%u", os.dwMajorVersion, os.dwMinorVersion, os.dwBuildNumber);
        WriteKeyValue("OS version number", ver);
        WriteKeyValue("OS service pack", os.szCSDVersion);
    }
    SYSTEM_INFO si;
    GetSystemInfo(&si);
    const char* dbg = IsDebuggerPresent() ? "yes" : "no";
    WriteKeyValue("Debugger present", dbg);
    char num[64];
    sprintf(num, "%u", si.dwNumberOfProcessors);
    WriteKeyValue("CPU count", num);
    const char* cpu = "x86 on x86-64";
    if (si.wProcessorArchitecture == 0) cpu = "x86";
    else if (si.wProcessorArchitecture == 9) cpu = "x86-64";
    WriteKeyValue("Processor type", cpu);
    sprintf(num, "%u", si.wProcessorLevel);
    WriteKeyValue("Processor level", num);
    sprintf(num, "%u", si.wProcessorRevision);
    WriteKeyValue("Processor revision", num);

    MEMORYSTATUSEX ms;
    ms.dwLength = 0x40;
    if (GlobalMemoryStatusEx(&ms)) {
        sprintf(num, "%d%%", ms.dwMemoryLoad);
        WriteKeyValue("Memory load", num);
        sprintf(num, "%I64d Mb", ms.ullTotalPhys >> 20);
        WriteKeyValue("Total physical memory", num);
        sprintf(num, "%I64d Mb", ms.ullAvailPhys >> 20);
        WriteKeyValue("Available physical memory", num);
        sprintf(num, "%I64d Mb", ms.ullTotalPageFile >> 20);
        WriteKeyValue("Total page file memory", num);
        sprintf(num, "%I64d Mb", ms.ullAvailPageFile >> 20);
        WriteKeyValue("Available page file memory", num);
        sprintf(num, "%I64d Mb", ms.ullTotalVirtual >> 20);
        WriteKeyValue("Total virtual memory", num);
        sprintf(num, "%I64d Mb", ms.ullAvailVirtual >> 20);
        WriteKeyValue("Free virtual memory", num);
    }
    return true;
}

// @ 0x0091f300
bool EA::Debug::ReportWriter::WriteApplicationInfo()
{
    WriteKeyValue("Language", "C++");
    WriteKeyValue("Compiler", "Microsoft Visual C++ compiler, version 1500");
    char path[0x104];
    DWORD n = GetModuleFileNameA(0, path, 0x104);
    if (n != 0 && n < 0x104)
        WriteKeyValue("App path", path);

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
                    WriteKeyValueFormatted("App version", "%u.%u.%u.%u", p[5], p[4], p[7], p[6]);
                }
            }
            LocalFree(data);
        }
    }
    return false;
}

// @ 0x0091f400
bool ReportWriter::WriteDisassembly(void* start, unsigned n, void* eip)
{
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

// @ 0x0091f7c0
bool ReportWriter_s0091_f520::WriteModuleList()
{
    void* h = LoadLibraryA("psapi.dll");
    if (!h) {
        v20("PSAPI is not available. Cannot dump module list.\r\n", 0);
        return false;
    }
    EnumProcessModules_t      epm = (EnumProcessModules_t)GetProcAddress(h, "EnumProcessModules");
    GetModuleFileNameExA_t    gmf = (GetModuleFileNameExA_t)GetProcAddress(h, "GetModuleFileNameExA");
    GetModuleBaseNameA_t      gmb = (GetModuleBaseNameA_t)GetProcAddress(h, "GetModuleBaseNameA");
    GetModuleInformation_t    gmi = (GetModuleInformation_t)GetProcAddress(h, "GetModuleInformation");
    void* proc = GetCurrentProcess();
    MODULEINFO mi;
    unsigned needed;
    char q1[0x105];   // 0x108 in size; declared smaller so it lands below q2 as in the original
    char q2[0x108];
    char out[0x28c];
    void* mods[256];
    if (epm(proc, mods, sizeof(mods), &needed)) {
        unsigned count = needed >> 2;
        if (count > 0x100) {
            v20("Module count exceeds our enumeration limit of 256. Only 256 will be displayed.\r\n", 0);
            count = 0x100;
        }
        for (unsigned i = 0; i < count; ++i) {
            if (!gmi(proc, mods[i], &mi, sizeof(mi))) {
                mi.EntryPoint = 0;
                mi.lpBaseOfDll = 0;
                mi.SizeOfImage = 0;
            }
            q1[0] = '"';
            if (!gmb(proc, mods[i], q1 + 1, 0x104))
                strcpy(q1 + 1, "<unknown>");
            AppendQuote(q1);
            q2[0] = '"';
            if (!gmf(proc, mods[i], q2 + 1, 0x104))
                strcpy(q2 + 1, "<unknown>");
            AppendQuote(q2);
            sprintf(out, "base 0x%08x size 0x%08x entry 0x%08x %-48s %s",
                    (unsigned)mi.lpBaseOfDll, mi.SizeOfImage, (unsigned)mi.EntryPoint, q1, q2);
            v20(out, 1);
        }
        return true;
    }
    v20("Failed to enumerate modules.\r\n", 0);
    return true;
}

// @ 0x0091fa10
bool EA::Debug::ReportWriter::WriteRegisterValues(void const * ctx)
{
    char buf[96];
    sprintf(buf, "%08x", *(unsigned*)((char*)ctx + 0xb8)); WriteKeyValue("eip", buf);
    sprintf(buf, "%08x", *(unsigned*)((char*)ctx + 0xb0)); WriteKeyValue("eax", buf);
    sprintf(buf, "%08x", *(unsigned*)((char*)ctx + 0xa4)); WriteKeyValue("ebx", buf);
    sprintf(buf, "%08x", *(unsigned*)((char*)ctx + 0xac)); WriteKeyValue("ecx", buf);
    sprintf(buf, "%08x", *(unsigned*)((char*)ctx + 0xa8)); WriteKeyValue("edx", buf);
    sprintf(buf, "%08x", *(unsigned*)((char*)ctx + 0xa0)); WriteKeyValue("esi", buf);
    sprintf(buf, "%08x", *(unsigned*)((char*)ctx + 0x9c)); WriteKeyValue("edi", buf);
    sprintf(buf, "%08x", *(unsigned*)((char*)ctx + 0xb4)); WriteKeyValue("ebp", buf);
    sprintf(buf, "%08x", *(unsigned*)((char*)ctx + 0xc0)); WriteKeyValue("efl", buf);
    sprintf(buf, "%08x", *(unsigned*)((char*)ctx + 0xc4)); WriteKeyValue("esp", buf);
    return true;
}

// @ 0x0091fbd0
bool EA::Debug::ReportWriter::WriteRegisterMemoryView(void const * ctx)
{
    unsigned u;
    u = *(unsigned*)((char*)ctx + 0xb0);
    if (u >= 0x10) WriteMemoryView((uint8_t*)u, 0x20, (uint8_t*)u, "eax ");
    u = *(unsigned*)((char*)ctx + 0xa4);
    if (u >= 0x10) WriteMemoryView((uint8_t*)u, 0x20, (uint8_t*)u, "ebx ");
    u = *(unsigned*)((char*)ctx + 0xac);
    if (u >= 0x10) WriteMemoryView((uint8_t*)u, 0x20, (uint8_t*)u, "ecx ");
    u = *(unsigned*)((char*)ctx + 0xa8);
    if (u >= 0x10) WriteMemoryView((uint8_t*)u, 0x20, (uint8_t*)u, "edx ");
    u = *(unsigned*)((char*)ctx + 0xa0);
    if (u >= 0x10) WriteMemoryView((uint8_t*)u, 0x20, (uint8_t*)u, "esi ");
    u = *(unsigned*)((char*)ctx + 0x9c);
    if (u >= 0x10) WriteMemoryView((uint8_t*)u, 0x20, (uint8_t*)u, "edi ");
    u = *(unsigned*)((char*)ctx + 0xb4);
    if (u >= 0x10) WriteMemoryView((uint8_t*)u, 0x20, (uint8_t*)u, "ebp ");
    return true;
}

// @ 0x0091fca0
bool EA::Debug::ReportWriter::WriteCallStack(void const * ctx)
{
    uint32_t frame[3];
    uint32_t a[4];
    uint32_t b[4];
    AddressRepCache repc;
    uint32_t addrs[0x80];
    char line[0x200];
    frame[0] = *(uint32_t*)((char*)ctx + 0xb8);
    frame[1] = *(uint32_t*)((char*)ctx + 0xc4);
    frame[2] = *(uint32_t*)((char*)ctx + 0xb4);
    unsigned n = CS_GetCallstack(addrs, 0x80, frame);
    if (n != 0) {
        AddressRepCache* cache = CS_a1c0();
        repc.Init();
        if (cache == 0)
            cache = &repc;
        for (unsigned i = 0; i < n; i++) {
            unsigned flags = cache->GetRep(0xf, addrs[i], a, b, 1);
            BeginSection("Callstack entry");
            CS_b580(addrs[i], line, 0x200);
            WriteText(line, 1);
            if (flags & 8) WriteText((const char*)a[3], 1);
            if (flags & 1) WriteFormatted("%s: %d\r\n", a[0], b[0]);
            if (flags & 2) WriteFormatted("%s + %d\r\n", a[1], b[1]);
            if (flags & 4) WriteText((const char*)a[2], 1);
            EndSection("Callstack entry");
        }
        repc.Shutdown();
        return true;
    }
    WriteText("Callstack not available\r\n", 0);
    return true;
}

// @ 0x0091fe60
bool EA::Debug::ReportWriter::WriteStackMemoryView(unsigned char const * lo, unsigned int len)
{
    unsigned lo_v = (unsigned)lo;
    unsigned stackLo = __readfsdword(4);
    unsigned stackHi = __readfsdword(8);
    unsigned a = lo_v - len;
    unsigned start = (a <= stackHi) ? stackHi : a;
    unsigned b = lo_v + len;
    unsigned end = (stackLo <= b) ? stackLo : b;
    start &= 0xfffffff0;
    end = (end + 0xf) & 0xfffffff0;
    if (stackHi <= lo_v && lo_v < stackLo && start < end) {
        WriteMemoryView((uint8_t*)start, (end - start), (uint8_t*)lo_v, 0);
        return true;
    }
    WriteText("Stack pointer appears to point to invalid memory.\r\n", 0);
    return true;
}
