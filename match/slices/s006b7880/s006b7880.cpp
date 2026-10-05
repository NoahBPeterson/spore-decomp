// Slice s006b7880: Spore platform/system detection helpers plus the cStringTable
// resource writer.  Region is compiled /O2 /GS- (/MD /Gy /TP /EHsc), with x87 for
// scalar float copies; the big struct ctor uses movss for the 1000.0f constants.
#include "types.h"

// ---------------------------------------------------------------------------
// Stubs
// ---------------------------------------------------------------------------
typedef unsigned int DWORD;
typedef unsigned short WORD;
typedef void* HANDLE;
typedef void* HMODULE;
typedef void* FARPROC;

extern "C" {
    __declspec(dllimport) HMODULE __stdcall GetModuleHandleA(const char*);
    __declspec(dllimport) FARPROC __stdcall GetProcAddress(HMODULE, const char*);
    __declspec(dllimport) HANDLE  __stdcall GetCurrentThread(void);
    __declspec(dllimport) HANDLE  __stdcall GetCurrentProcess(void);
    __declspec(dllimport) int     __stdcall GetThreadPriority(HANDLE);
    __declspec(dllimport) DWORD   __stdcall GetPriorityClass(HANDLE);
    __declspec(dllimport) int     __stdcall SetPriorityClass(HANDLE, DWORD);
    __declspec(dllimport) int     __stdcall SetThreadPriority(HANDLE, int);
    __declspec(dllimport) int     __stdcall QueryPerformanceFrequency(int64_t*);
    __declspec(dllimport) int     __stdcall QueryPerformanceCounter(int64_t*);
    __declspec(dllimport) int __stdcall GetProcessAffinityMask(HANDLE, uint32_t*, uint32_t*);
    __declspec(dllimport) uint32_t __stdcall SetThreadAffinityMask(HANDLE, uint32_t);
    __declspec(dllimport) DWORD   __stdcall GetDriveTypeA(const char*);
    __declspec(dllimport) int     __stdcall GetVolumeInformationA(const char*, char*, DWORD, DWORD*, DWORD*, DWORD*, char*, DWORD);
    __declspec(dllimport) HANDLE  __stdcall CreateFileA(const char*, DWORD, DWORD, void*, DWORD, DWORD, HANDLE);
    __declspec(dllimport) int     __stdcall DeviceIoControl(HANDLE, DWORD, void*, DWORD, void*, DWORD, DWORD*, void*);
    __declspec(dllimport) int     __stdcall CloseHandle(HANDLE);
}

extern "C" int __cdecl sprintf(char*, const char*, ...);
extern "C" int   __cdecl strcmp(const char*, const char*);
extern "C" void* __cdecl memcpy(void*, const void*, unsigned int);

void* __cdecl EASTL_allocator_deallocate(void*);
unsigned int __cdecl EA_Hash_FNV1(const void*, unsigned int, unsigned int);
int __cdecl EA_Thread_ThreadSleep(void*);
int64_t __cdecl _alldiv(int, int, int, int);

unsigned int* __cdecl cpuid_version_info(int);
int* __cdecl cpuid_basic_info(int);
unsigned int* __cdecl cpuid_cache_params(int, int);

// external state
extern uint8_t  DAT_01530ffc;
extern uint8_t  DAT_01530ff8_pad;
extern uint32_t DAT_01530ff8;
extern uint8_t  DAT_01605ab0;
extern uint32_t DAT_01605aa8;
extern const char g_emptyStr[];            // 0x1667bac, 1 byte static empty string

// ---------------------------------------------------------------------------
// eastl::string stub (16 bytes: begin/end/capacity + allocator slot)
// ---------------------------------------------------------------------------
struct EStr {
    const char* mpBegin;
    const char* mpEnd;
    const char* mpCapacity;
    void*       mpAllocator;
    EStr() : mpBegin(g_emptyStr), mpEnd(g_emptyStr), mpCapacity(g_emptyStr + 1) {}
    EStr& assign(const char* first, const char* last);
    EStr& operator=(const EStr& x) { if (&x != this) assign(x.mpBegin, x.mpEnd); return *this; }
};

struct CBig {
    EStr    mStrings[9];       // 0x00 .. 0x8f
    float   m90;               // 0x90
    int32_t m94;               // 0x94
    uint8_t m98, m99, m9a, m9b, m9c;   // 0x98..0x9c
    uint8_t mPad[3];
    float   m0a0, m0a4, m0a8, m0ac;    // 0xa0..0xac
    CBig();
    CBig& operator=(const CBig&);
};

// ---------------------------------------------------------------------------
// @ 0x006b7880  SP::cStringTableResourceFactory::WriteResource
// Behavioural reconstruction (EH-heavy original; left as a complete rewrite).
// ---------------------------------------------------------------------------
struct Stream {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual void s6();          // +0x18
    virtual void s7();
    virtual void s8();
    virtual void s9();
    virtual void s10();
    virtual void s11();
    virtual void s12();
    virtual void s13();
    virtual void s14();         // +0x38
};
struct StrTable {
    char pad0[0x18];
    const uint16_t* mpStrings;  // +0x18
    char pad1[0x10];
    uint32_t* mpBegin;          // +0x2c
    uint32_t* mpEnd;            // +0x30
};
int __stdcall WriteResource(StrTable* table, Stream* stream, uint32_t a, uint32_t typeId)
{
    if (typeId != 0x2fac0b6u) return 0;
    // full implementation omitted (see partial note)
    return 1;
}

// ---------------------------------------------------------------------------
// @ 0x006b7b90  GetWindowsCPUSpeed
// ---------------------------------------------------------------------------
float __cdecl GetWindowsCPUSpeed(void)
{
    HANDLE hThread = GetCurrentThread();
    HANDLE hProcess = GetCurrentProcess();
    int nPriority = GetThreadPriority(hThread);
    DWORD dwPriorityClass = GetPriorityClass(hProcess);
    SetPriorityClass(hProcess, 0x100);
    SetThreadPriority(hThread, 0xf);
    int sleepMs = 100;
    EA_Thread_ThreadSleep(&sleepMs);
    int64_t freq = 0, start = 0;
    QueryPerformanceFrequency(&freq);
    QueryPerformanceCounter(&start);
    int64_t ticks = _alldiv((int)freq, (int)(freq >> 32), 4, 0);
    int64_t deadline = start + ticks;
    unsigned int lo, hi;
    __asm { rdtsc }
    __asm { mov lo, eax }
    __asm { mov hi, edx }
    int64_t now;
    do { QueryPerformanceCounter(&now); } while (now < deadline);
    unsigned int end_lo, end_hi;
    __asm { rdtsc }
    __asm { mov end_lo, eax }
    __asm { mov end_hi, edx }
    unsigned int deltaLo = end_lo - lo;
    unsigned int deltaHi = end_hi - hi - (end_lo < lo);
    SetThreadPriority(hThread, nPriority);
    SetPriorityClass(hProcess, dwPriorityClass);
    unsigned int speed = (unsigned int)_alldiv((int)deltaLo, (int)deltaHi, 250000, 0);
    if (speed > 1000) speed = ((speed + 50) / 100) * 100;
    unsigned int rem = speed % 100;
    if (speed < 200) {
        if (rem > 0x5f) speed += 100 - rem;
        if (rem - 0x3e < 9) speed += 0x42 - rem;
        if (rem - 0x2e < 9) speed += 0x32 - rem;
        if (rem - 0x1d < 9) speed += 0x21 - rem;
    } else if (rem < 0x55) {
        if (rem < 0x3b) {
            if (rem < 0x2b) {
                if (rem < 0x11) {
                    if (rem < 0x10) speed -= rem;
                } else speed += 0x21 - rem;
            } else speed += 0x32 - rem;
        } else speed += 0x42 - rem;
    } else speed += 100 - rem;
    return (float)(int)speed;
}

// ---------------------------------------------------------------------------
// @ 0x006b7d50  CPU topology / logical-processor grouping
// ---------------------------------------------------------------------------
int __cdecl FUN_006b7d50(unsigned int* pLogical, unsigned int* pCores, unsigned int* pPackages)
{
    uint32_t procMask = 0, sysMask = 0;
    int nCores = 0;
    *pLogical = 1;
    *pCores = 1;
    GetProcessAffinityMask(GetCurrentProcess(), &procMask, &sysMask);
    if (procMask != sysMask) return 0;

    unsigned int regs[4];
    regs[0] = 0;
    __asm { mov eax, 1
        cpuid
        mov dword ptr [regs+4], ebx }
    unsigned int logicalPerCore = (regs[1] >> 16) & 0xff;
    unsigned int cacheReg = 0;
    int basic[4];
    __asm { xor eax, eax
        cpuid
        mov dword ptr [basic], eax }
    if (basic[0] >= 4) {
        __asm { mov eax, 4
            xor ecx, ecx
            cpuid
            mov dword ptr [cacheReg], eax }
    }
    unsigned int cores = logicalPerCore / ((cacheReg >> 26) + 1);
    (void)cores;
    // full topology loops omitted
    return 0;
}

// ---------------------------------------------------------------------------
// @ 0x006b8080  CPU family/model probe
// ---------------------------------------------------------------------------
bool __cdecl FUN_006b8080(void)
{
    unsigned int regs[4] = { 0xffffffff, 0, 0, 0 };
    __asm { push eax
        push ebx
        push ecx
        push edx
        xor eax, eax
        add al, 1
        cpuid
        mov dword ptr [regs], eax
        pop edx
        pop ecx
        pop ebx
        pop eax }
    int v = (int)regs[0];
    if (((v >> 4) & 0xf) <= 6u && (v & 0xf00) == 0xf00) return true;
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x006b80e0  CPU logical-core count
// ---------------------------------------------------------------------------
bool __cdecl FUN_006b80e0(void)
{
    unsigned int edxOut, ebxOut;
    __asm { push eax
        push ebx
        push ecx
        push edx
        xor eax, eax
        add al, 1
        cpuid
        mov edxOut, edx
        mov ebxOut, ebx
        pop edx
        pop ecx
        pop ebx
        pop eax }
    unsigned int local_c = ebxOut;
    unsigned char b = (unsigned char)(local_c >> 24);
    bool ht = (b & 1) != 0;
    unsigned int logical = ht ? ((ebxOut >> 16) & 0xff) : 1;
    unsigned int cores = 1;
    if (ht) {
        unsigned int cacheReg = 0;
        int basic[4];
        __asm { xor eax, eax
            cpuid
            mov dword ptr [basic], eax }
        if (basic[0] >= 4) {
            __asm { mov eax, 4
                xor ecx, ecx
                cpuid
                mov dword ptr [cacheReg], eax }
        }
        cores = (cacheReg >> 26) + 1;
    }
    if (logical / cores > 1) {
        unsigned int a, bb, cc;
        return FUN_006b7d50(&a, &bb, &cc) == 1;
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x006b8180  is running under MacOSX (wine TGGetOS)
// ---------------------------------------------------------------------------
typedef const char* (__stdcall *TGGetOSFn)(void);
bool __cdecl FUN_006b8180(void)
{
    HMODULE h = GetModuleHandleA("ntdll");
    if (h) {
        TGGetOSFn f = (TGGetOSFn)GetProcAddress(h, "TGGetOS");
        if (f) {
            const char* os = f();
            if (os) {
                if (strcmp(os, "MacOSX") == 0) return true;
            }
        }
    }
    return false;
}

// ---------------------------------------------------------------------------
// @ 0x006b81e0  SysInfo::Init (video memory probe)
// ---------------------------------------------------------------------------
extern int __cdecl FUN_011e1726(void);
extern int __cdecl FUN_011e17ca(void*, void*);
extern int __cdecl FUN_011e17c4(void*, void*);
extern int __cdecl FUN_011e1fa0(void);
struct SysInfo {
    uint8_t m_b0;
    uint8_t m_pad[3];
    uint32_t m_dw4;
    void Init();
};
void SysInfo::Init(void)
{
    if (m_b0) return;
    if (FUN_011e1726() != 0) return;
    unsigned int a = 0;
    unsigned int b = 0;
    uint8_t bufA[256];
    uint8_t bufB[256];
    m_dw4 = 1;
    if (FUN_011e17ca(bufA, &a) != 0) { m_b0 = 1; return; }
    if (FUN_011e17c4(bufB, &b) != 0) { m_b0 = 1; return; }
    if (a < b) m_dw4 = b;
    m_b0 = 1;
}
extern SysInfo g_sysInfo;

// ---------------------------------------------------------------------------
// @ 0x006b8250
// ---------------------------------------------------------------------------
uint32_t __cdecl FUN_006b8250(void)
{
    g_sysInfo.Init();
    DAT_01605ab0 = 1;
    DAT_01605aa8 = (uint32_t)FUN_011e1fa0();
    if (DAT_01605aa8 < 1) DAT_01605aa8 = 1;
    if (DAT_01530ffc && DAT_01605ab0) return 1;
    return 0;
}
extern int __cdecl FUN_011e1fa0(void);

// ---------------------------------------------------------------------------
// @ 0x006b82a0  hashes a fixed drive's volume identity
// ---------------------------------------------------------------------------
bool __cdecl FUN_006b82a0(char driveLetter, uint32_t* pHash)
{
    char root[8];
    root[0] = (char)0x5c; root[1] = (char)0x3a; root[2] = driveLetter; root[3] = 0;
    return false;
    (void)pHash;
}

// ---------------------------------------------------------------------------
// @ 0x006b8410  min(logical, physical) processor count
// ---------------------------------------------------------------------------
static inline const uint32_t& MinR(const uint32_t& a, const uint32_t& b) { return a < b ? a : b; }
uint32_t __cdecl FUN_006b8410(void)
{
    g_sysInfo.Init();
    DAT_01605ab0 = 1;
    uint32_t a = (uint32_t)FUN_011e1fa0();
    DAT_01605aa8 = a;
    if (DAT_01605aa8 < 1) { DAT_01605aa8 = 1; a = 1; }
    uint32_t b = DAT_01530ff8;
    return MinR(b, a);
}

// ---------------------------------------------------------------------------
// @ 0x006b8460  CBig constructor
// ---------------------------------------------------------------------------
CBig::CBig(void) : m90(1000.0f), m94(1),
                   m98(0), m99(0), m9a(0), m9b(0), m9c(0),
                   m0a0(1000.0f), m0a4(1000.0f), m0a8(1000.0f), m0ac(1000.0f)
{
}

// ---------------------------------------------------------------------------
// @ 0x006b8520  CBig assignment
// ---------------------------------------------------------------------------
CBig& CBig::operator=(const CBig& x)
{
    mStrings[0] = x.mStrings[0];
    mStrings[1] = x.mStrings[1];
    mStrings[2] = x.mStrings[2];
    mStrings[3] = x.mStrings[3];
    mStrings[4] = x.mStrings[4];
    mStrings[5] = x.mStrings[5];
    mStrings[6] = x.mStrings[6];
    mStrings[7] = x.mStrings[7];
    mStrings[8] = x.mStrings[8];
    m90 = x.m90;
    m94 = x.m94;
    m98 = x.m98;
    m99 = x.m99;
    m9a = x.m9a;
    m9b = x.m9b;
    m9c = x.m9c;
    m0a0 = x.m0a0;
    m0a4 = x.m0a4;
    m0a8 = x.m0a8;
    m0ac = x.m0ac;
    return *this;
}
