// src/game/SPEngine/SPSystemInfo.cpp -- migrated from slice(s) s006b8680 by tools/migrate/rewrite.py
// Object file: SPEngine/SPSystemInfo.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// unnamed retail callees and globals (address in the comment)
extern "C" __declspec(dllimport) int __stdcall GetVersionExA(void*);
extern "C" __declspec(dllimport) void __stdcall GetSystemInfo(void*);
extern "C" __declspec(dllimport) int __stdcall GlobalMemoryStatusEx(void*);
extern "C" __declspec(dllimport) int __cdecl sprintf(char*, const char*, ...);
extern "C" unsigned int __cdecl strlen(const char*);
extern "C" void* __cdecl memset(void*, int, unsigned int);
extern "C" bool __cdecl FUN_006b82a0(char, uint32_t*);
extern uint8_t DAT_01605ab4;
extern uint8_t DAT_01605d34;
extern "C" __declspec(dllimport) void* __stdcall LocalFree(void*);
#include <intrin.h>

// ---- items of slice s006b8680 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int DWORD;
typedef void* HMODULE;
typedef void* FARPROC;
extern "C" __declspec(dllimport) int __stdcall GetComputerNameExA(int, char*, DWORD*);
extern "C" __declspec(dllimport) int __stdcall GetUserNameW(wchar_t*, DWORD*);
extern "C" __declspec(dllimport) HMODULE __stdcall LoadLibraryA(const char*);
extern "C" __declspec(dllimport) FARPROC __stdcall GetProcAddress(HMODULE, const char*);
extern "C" __declspec(dllimport) int __stdcall FreeLibrary(HMODULE);
extern "C" __declspec(dllimport) int __stdcall GetVersionExA(void*);
extern "C" __declspec(dllimport) void __stdcall GetSystemInfo(void*);
extern "C" __declspec(dllimport) int __stdcall GlobalMemoryStatusEx(void*);
extern "C" __declspec(dllimport) int __cdecl sprintf(char*, const char*, ...);
extern "C" unsigned int __cdecl strlen(const char*);
extern "C" void* __cdecl memset(void*, int, unsigned int);
extern "C" bool __cdecl FUN_006b82a0(char, uint32_t*);
struct CBig;
extern "C" void __cdecl FUN_006b8680(CBig*);
extern uint8_t DAT_01605ab4;
extern uint8_t DAT_01605d34;
struct EStr {
    const char* mpBegin;
    const char* mpEnd;
    const char* mpCapacity;
    void*       mpAllocator;
    EStr();
    EStr& assign(const char*, const char*);           // 0x454cb0
    EStr& assign(const char*);                        // 0x6a4380
    EStr& append(const char*, const char*);           // 0x455d60
    EStr& sprintf(const char*, ...);                  // 0x472fe0 (cdecl, this pushed)
    EStr& append_sprintf(const char*, ...);           // 0x5f9450 (cdecl, this pushed)
    EStr& operator=(const EStr& x) { if (&x != this) assign(x.mpBegin, x.mpEnd); return *this; }
};
struct CBig {
    EStr    mStrings[9];
    float   m90;
    int32_t m94;
    uint8_t m98, m99, m9a, m9b, m9c;
    uint8_t mPad[3];
    float   m0a0, m0a4, m0a8, m0ac;
    CBig();
    ~CBig();
    CBig& operator=(const CBig&);
};
struct OSVI {
    DWORD dwOSVersionInfoSize, dwMajorVersion, dwMinorVersion, dwBuildNumber, dwPlatformId;
    char  szCSDVersion[128];
    uint16_t wServicePackMajor, wServicePackMinor, wSuiteMask;
    uint8_t  wProductType, wReserved;
};
struct SYSINFO {
    uint16_t wProcessorArchitecture, wReserved;
    DWORD dwPageSize;
    void *lpMinimumApplicationAddress, *lpMaximumApplicationAddress;
    DWORD dwActiveProcessorMask, dwNumberOfProcessors, dwProcessorType, dwAllocationGranularity;
    uint16_t wProcessorLevel, wProcessorRevision;
};
struct MEMSTATEX {
    DWORD dwLength, dwMemoryLoad;
    uint64_t ullTotalPhys, ullAvailPhys, ullTotalPageFile, ullAvailPageFile, ullTotalVirtual, ullAvailVirtual, ullAvailExtendedVirtual;
};
extern "C" __declspec(dllimport) DWORD __stdcall GetModuleFileNameA(HMODULE, char*, DWORD);
extern "C" __declspec(dllimport) void* __stdcall LocalAlloc(DWORD, DWORD);
extern "C" __declspec(dllimport) void* __stdcall LocalFree(void*);
DWORD __stdcall FUN_GetFileVersionInfoSizeA(const char*, DWORD*);                 // 0x11e170e
int   __stdcall FUN_GetFileVersionInfoA(const char*, DWORD, DWORD, void*);        // 0x11e1708
int   __stdcall FUN_VerQueryValueA(const void*, const char*, void**, DWORD*);     // 0x11e1702
const char* __cdecl StrIStr(const char* hay, const char* needle);                 // 0x92cc00
float __cdecl GetWindowsCPUSpeed(void);                                           // 0x6b7b90
bool  __cdecl FUN_006b80e0(void);
bool  __cdecl FUN_006b8080(void);
bool  __cdecl FUN_006b8180(void);
extern CBig g_SystemInfoCache;   // 0x1605c98
template<int N> inline void SetLit(EStr& s, const char (&lit)[N]) { s.assign(lit, lit + (N - 1)); }
inline void SetStr(EStr& s, const char* b) { s.assign(b, b + strlen(b)); }
// ---- items of slice s006b8680 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" __declspec(dllimport) int __stdcall GetComputerNameExA(int, char*, DWORD*);
extern "C" __declspec(dllimport) int __stdcall GetUserNameW(wchar_t*, DWORD*);
extern "C" __declspec(dllimport) HMODULE __stdcall LoadLibraryA(const char*);
extern "C" __declspec(dllimport) FARPROC __stdcall GetProcAddress(HMODULE, const char*);
extern "C" __declspec(dllimport) int __stdcall FreeLibrary(HMODULE);
extern "C" void __cdecl FUN_006b8680(CBig*);
extern "C" __declspec(dllimport) DWORD __stdcall GetModuleFileNameA(HMODULE, char*, DWORD);
extern "C" __declspec(dllimport) void* __stdcall LocalAlloc(DWORD, DWORD);
extern CBig g_SystemInfoCache;   // 0x1605c98

// @ 0x006b8680
extern "C" void __cdecl FUN_006b8680(CBig* out)
{
    if (DAT_01605ab4) {
        *out = g_SystemInfoCache;
        return;
    }
    out->m0a0 = 0.0f; out->m0a4 = 0.0f; out->m0a8 = 0.0f; out->m0ac = 0.0f;

    char  host[256];
    wchar_t user[256];
    DWORD len = 0x100;
    if (GetComputerNameExA(3, host, &len) > 0)
        SetStr(out->mStrings[0], host);
    len = 0x100;
    if (GetUserNameW(user, &len) > 0)
        out->mStrings[1].sprintf("%ls", user);
    SetLit(out->mStrings[2], "Windows on X86");

    OSVI osvi;
    memset(&osvi, 0, sizeof(osvi));
    osvi.dwOSVersionInfoSize = sizeof(osvi);
    bool hasProductInfo = false;
    HMODULE hk = LoadLibraryA("kernel32.dll");
    if (hk) {
        if (GetProcAddress(hk, "GetProductInfo")) hasProductInfo = true;
        FreeLibrary(hk);
    }
    if (GetVersionExA(&osvi)) {
        EStr& os = out->mStrings[3];
        if (osvi.dwMajorVersion >= 6 || hasProductInfo) SetLit(os, "Windows Vista");
        else if (osvi.dwMajorVersion < 5) os.assign("Windows 98 or earlier");
        else if (osvi.dwMinorVersion == 0) os.assign("Windows 2000");
        else if (osvi.dwMinorVersion == 1) os.assign("Windows XP");
        else os.assign("Windows Server 2003");
        os.append(", ", ", " + 2);
        os.append(osvi.szCSDVersion, osvi.szCSDVersion + strlen(osvi.szCSDVersion));
        sprintf(host, "%u.%u.%u", osvi.dwMajorVersion, osvi.dwMinorVersion, osvi.dwBuildNumber);
        SetStr(out->mStrings[4], host);
    }

    // CPUID leaf 0: the 12 vendor bytes come back in EBX, EDX, ECX (in that order).
    char vendor[64];
    int cpuidRegs[4];
    __cpuid(cpuidRegs, 0);
    *(int*)(vendor + 0) = cpuidRegs[1];        // EBX
    *(int*)(vendor + 4) = cpuidRegs[3];        // EDX
    *(int*)(vendor + 8) = cpuidRegs[2];        // ECX
    vendor[12] = 0;
    bool isAmd = StrIStr(vendor, "AMD") != 0;
    bool isIntel;
    if (!isAmd) isIntel = StrIStr(vendor, "INTEL") != 0;
    else isIntel = false;
    SetStr(out->mStrings[6], vendor);

    SYSINFO si;
    GetSystemInfo(&si);
    EStr& arch = out->mStrings[5];
    if (si.wProcessorArchitecture == 0) SetLit(arch, "arch=x86");
    else if (si.wProcessorArchitecture == 9) SetLit(arch, "arch=x86-64");
    else if (si.wProcessorArchitecture == 10) arch.assign("arch=x86 on x86-64");
    else arch.assign("arch=unknown");
    arch.append_sprintf(", level=%u, revision=%u, processors=%u",
                        (unsigned)si.wProcessorLevel, (unsigned)si.wProcessorRevision, si.dwNumberOfProcessors);

    out->m90 = GetWindowsCPUSpeed();
    out->m94 = si.dwNumberOfProcessors;
    out->m9a = (isIntel && FUN_006b80e0()) ? 1 : 0;
    out->m9b = (isIntel && FUN_006b8080()) ? 1 : 0;
    out->m99 = isIntel;
    out->m98 = isAmd;
    out->m9c = FUN_006b8180();

    MEMSTATEX ms;
    memset(&ms, 0, sizeof(ms));
    ms.dwLength = sizeof(ms);
    if (GlobalMemoryStatusEx(&ms)) {
        out->m0a0 = (float)(ms.ullTotalPhys >> 20);
        out->m0a4 = (float)(ms.ullAvailPhys >> 20);
        out->m0a8 = (float)(ms.ullTotalPageFile >> 20);
        out->m0ac = (float)(ms.ullAvailPageFile >> 20);
    }

    char path[260];
    DWORD n = GetModuleFileNameA(0, path, 0x104);
    if (n != 0 && n < 0x104)
        SetStr(out->mStrings[8], path);

    DWORD dummy;
    DWORD vsz = FUN_GetFileVersionInfoSizeA(path, &dummy);
    if (vsz > 0) {
        void* data = LocalAlloc(0x40, vsz);
        if (data) {
            void* fixed;
            DWORD flen;
            if (FUN_GetFileVersionInfoA(path, 0, vsz, data) && FUN_VerQueryValueA(data, "\\", &fixed, &flen)) {
                uint16_t* v = (uint16_t*)fixed;
                out->mStrings[7].sprintf("%u.%u.%u.%u", (unsigned)v[5], (unsigned)v[4], (unsigned)v[7], (unsigned)v[6]);
            }
            LocalFree(data);
        }
    }
    g_SystemInfoCache = *out;
    DAT_01605ab4 = 1;
}

// @ 0x006b8ca0
uint32_t __cdecl FUN_006b8ca0(uint32_t drive)
{
    if (DAT_01605ab4 == 0) {
        CBig temp;
        FUN_006b8680(&temp);
        temp.~CBig();
    }
    if (DAT_01605d34 != 0) return 0x64e4c607;
    uint32_t h = 0x811c9dc5;
    char c = FUN_006b82a0((char)drive, &h);
    return -(uint32_t)(c != 0) & h;
}
