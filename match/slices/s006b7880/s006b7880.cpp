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

extern "C" void __cpuid(int regs[4], int functionId);   // MSVC intrinsic
#pragma intrinsic(__cpuid)

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
// SP::cStringTableResourceFactory::WriteResource (see below)
// ---------------------------------------------------------------------------
struct Writer {
    virtual void w0(); virtual void w1(); virtual void w2(); virtual void w3();
    virtual void w4(); virtual void w5(); virtual void w6(); virtual void w7();
    virtual void w8(); virtual void w9(); virtual void w10(); virtual void w11();
    virtual void w12(); virtual void w13();
    virtual void Write(const void* p, int n);       // +0x38
};
struct Stream {
    virtual void s0();
    virtual void s1();
    virtual void s2();
    virtual void s3();
    virtual void s4();
    virtual void s5();
    virtual Writer* GetWriter();     // +0x18
};
struct StrTable {
    char pad0[0x18];
    const uint16_t* mpStrings;  // +0x18
    char pad1[0x10];
    uint32_t* mpBegin;          // +0x2c
    uint32_t* mpEnd;            // +0x30
};

extern const char g_crlf[];                                        // 0x01409be4 "\r\n"
extern "C" void* __cdecl memcpy_thunk(void*, const void*, unsigned);   // 0x011e0744 (memcpy)
extern "C" void  __cdecl FreeArray(void*);                          // 0x00f47380
extern "C" int   __cdecl StrncpyUTF8ToUTF16(char* dst, int dstCap, const wchar_t* src, int srcLen); // 0x0093cf10

struct ByteVec {
    char* mpBegin;
    char* mpEnd;
    char* mpCap;
    ByteVec() : mpBegin(0), mpEnd(0), mpCap(0) {}
    ~ByteVec() { if (mpBegin && ((int*)mpBegin)[-1] != 0) FreeArray(mpBegin); }
    void reserve(unsigned n);                                   // 0x006b6b70
    void insert(char* pos, unsigned n, const char& v);          // 0x006b7180
    void resize(unsigned n) {
        unsigned sz = (unsigned)(mpEnd - mpBegin);
        if (sz < n) {
            insert(mpEnd, n - sz, 0);
        } else {
            char* first = mpBegin + n;
            memcpy_thunk(first, mpEnd, 0);
            mpEnd = first;
        }
    }
};

#pragma intrinsic(strlen, wcslen)
extern "C" unsigned strlen(const char*);
extern "C" unsigned wcslen(const wchar_t*);

// @ 0x006b7880  SP::cStringTableResourceFactory::WriteResource
bool __stdcall WriteResource(StrTable* table, Stream* stream, uint32_t a, uint32_t typeId)
{
    bool ok = false;
    if (typeId == 0x2fac0b6u) {
        Writer* w = stream->GetWriter();
        ByteVec buf;
        buf.reserve(0x400);
        int eolLen = (int)strlen(g_crlf);
        char b[28];
        b[0] = (char)0xef; b[1] = (char)0xbb; b[2] = (char)0xbf;
        b[3] = 0; b[4] = 0; b[5] = 0; b[6] = 0; b[7] = 0;
        b[8] = '\\'; b[9] = 'n'; b[10] = '0'; b[11] = 'x';
        b[12] = '0'; b[13] = '1'; b[14] = '2'; b[15] = '3'; b[16] = '4'; b[17] = '5';
        b[18] = '6'; b[19] = '7'; b[20] = '8'; b[21] = '9'; b[22] = 'A'; b[23] = 'B';
        b[24] = 'C'; b[25] = 'D'; b[26] = 'E'; b[27] = 'F';
        char* bom = b; char* esc = b + 8; char* px = b + 10; char* hex = b + 12;
        w->Write(bom, 3);
        uint32_t* end = table->mpEnd;
        for (uint32_t* e = table->mpBegin; e != end; ) {
            uint32_t* cur = e;
            e += 2;
            bom[0] = hex[*cur >> 28];
            bom[1] = hex[(*cur >> 24) & 0xf];
            bom[2] = hex[(*cur >> 20) & 0xf];
            bom[3] = hex[(*cur >> 16) & 0xf];
            bom[4] = hex[(*cur >> 12) & 0xf];
            bom[5] = hex[(*cur >> 8) & 0xf];
            bom[6] = hex[(*cur >> 4) & 0xf];
            bom[7] = hex[*cur & 0xf];
            w->Write(px, 2);
            w->Write(bom, 8);
            w->Write(g_crlf, eolLen);
            const wchar_t* str = (const wchar_t*)(table->mpStrings + cur[1]);
            int n = (int)wcslen(str);
            buf.resize((unsigned)((n * 3 + 3) * 2));
            int size = (int)(buf.mpEnd - buf.mpBegin);
            if (StrncpyUTF8ToUTF16(buf.mpBegin, size, str, n) != 0) {
                int start = 0;
                int i = 0;
                while (i < size) {
                    while (i < size && buf.mpBegin[i] != '\n') i++;
                    if (i - start > 0) w->Write(buf.mpBegin + start, i - start);
                    if (i < size && buf.mpBegin[i] == '\n') w->Write(esc, 2);
                    i++;
                    start = i;
                }
            }
            w->Write(g_crlf, eolLen);
        }
        ok = true;
    }
    return ok;
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
// CPU topology / logical-processor grouping
// ---------------------------------------------------------------------------
extern "C" void ApplyThreadAffinity(uint32_t* mask);   // 0x921df0 cdecl

// Number of bits needed to represent x-1 (0 for x <= 1), i.e. bsr(x-1)+1.
static unsigned int BitsFor(unsigned int x)
{
    unsigned int bits = 0;
    for (unsigned int v = x - 1; v != 0; v >>= 1)
        bits++;
    return bits;
}

// Walk every logical processor in the current affinity mask, derive its core
// and package id from the initial APIC id and count the distinct combinations.
// *pCount gets the number of processors seen, *pCorePairs / *pCoreIds the
// numbers of distinct core/package pairs and of distinct logical processors.
// @ 0x006b7d50
int __cdecl FUN_006b7d50(unsigned int* pCount, unsigned int* pCorePairs, unsigned int* pCoreIds)
{
    uint32_t procMask = 0, sysMask = 0;
    int regs[4];

    *pCorePairs = 1;
    *pCoreIds = 1;
    GetProcessAffinityMask(GetCurrentProcess(), &procMask, &sysMask);
    if (procMask != sysMask) return false;

    __cpuid(regs, 1);
    uint32_t logicalPerCore = ((uint32_t)regs[1] >> 16) & 0xff;
    uint32_t cacheReg = 0;
    __cpuid(regs, 0);
    if ((uint32_t)regs[0] >= 4) {
        __cpuid(regs, 4);
        cacheReg = (uint32_t)regs[0];
    }
    uint32_t cores = logicalPerCore / ((cacheReg >> 26) + 1);

    uint8_t  coreId[256];
    uint8_t  pkgId[256];
    uint8_t  lpcId[256];
    uint32_t count = 0;
    uint32_t apicTmp = 0;
    for (unsigned int i = 0, bit = 1; bit <= sysMask && bit != 0; i++, bit <<= 1) {
        if (SetThreadAffinityMask(GetCurrentThread(), bit) == 0)
            continue;
        ApplyThreadAffinity(&apicTmp);
        __cpuid(regs, 1);
        uint8_t apic = (uint8_t)((uint32_t)regs[1] >> 24);
        coreId[i] = (uint8_t)(apic & (uint8_t)((0xffu << BitsFor(cores & 0xff)) ^ 0xffu));
        pkgId[i] = (uint8_t)((apic >> BitsFor(cores)) &
                             (uint8_t)((0xffu << BitsFor((cacheReg >> 26) + 1)) ^ 0xffu));
        lpcId[i] = (uint8_t)(apic & (uint8_t)((0xffu << BitsFor(logicalPerCore)) ^ 0xffu));
        count++;
    }
    SetThreadAffinityMask(GetCurrentThread(), procMask);
    {
        uint32_t tmp = 0;
        ApplyThreadAffinity(&tmp);
    }

    uint32_t seen[256];                // bitmask of the processors per signature
    uint8_t  sigs[256];                // distinct (package, logical) signatures
    *pCount = count;
    sigs[0] = (uint8_t)(pkgId[0] | lpcId[0]);
    seen[0] = 1;
    if (count > 1) {
        unsigned int sig = 2;
        for (uint32_t i = 1; i < count; i++, sig <<= 1) {
            uint8_t s = (uint8_t)(pkgId[i] | lpcId[i]);
            unsigned int n = *pCorePairs;
            unsigned int j = 0;
            while (j < n && sigs[j] != s)
                j++;
            if (j == n) {
                sigs[j] = s;
                seen[j] = sig;
                *pCorePairs = n + 1;
            } else {
                seen[j] |= sig;
            }
        }
    }

    sigs[0] = lpcId[0];
    seen[0] = 1;
    if (count > 1) {
        unsigned int sig = 2;
        for (uint32_t i = 1; i < count; i++, sig <<= 1) {
            uint8_t s = lpcId[i];
            unsigned int n = *pCoreIds;
            unsigned int j = 0;
            while (j < n && sigs[j] != s)
                j++;
            if (j == n) {
                sigs[j] = s;
                seen[j] = sig;
                *pCoreIds = n + 1;
            } else {
                seen[j] |= sig;
            }
        }
    }
    return cores > 1 && count > *pCorePairs;
}

// ---------------------------------------------------------------------------
// @ 0x006b8080  CPU family/model probe
// ---------------------------------------------------------------------------
bool __cdecl FUN_006b8080(void)
{
    int regs[4];
    __cpuid(regs, 1);
    int v = regs[0];
    if ((v & 0xf00) != 0xf00) return false;
    if (((v >> 4) & 0xf) > 6) return false;
    return true;
}

// ---------------------------------------------------------------------------
// @ 0x006b80e0  CPU logical-core count
// ---------------------------------------------------------------------------
bool __cdecl FUN_006b80e0(void)
{
    int regs[4];
    __cpuid(regs, 1);
    unsigned int ebx = (unsigned int)regs[1];
    unsigned int edx = (unsigned int)regs[3];
    bool ht = ((edx >> 28) & 1) != 0;
    unsigned int logical = ht ? ((ebx >> 16) & 0xff) : 1;
    unsigned int cores = 1;
    if (ht) {
        unsigned int cacheReg = 0;
        int basic[4];
        __cpuid(basic, 0);
        if (basic[0] >= 4) {
            int leaf4[4];
            __cpuid(leaf4, 4);
            cacheReg = (unsigned int)leaf4[0];
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
extern "C" uint32_t __cdecl HashBytes(const void* data, unsigned len, uint32_t seed); // 0x932e50

struct DiskExtent {                      // DISK_EXTENT, 0x18 bytes
    uint32_t mDiskNumber;
    uint32_t mPad;
    uint64_t mStartingOffset;
    uint64_t mExtentLength;
};
struct VolumeDiskExtents {               // VOLUME_DISK_EXTENTS
    uint32_t    mNumberOfDiskExtents;
    uint32_t    mPad;
    DiskExtent  mExtents[32];
};

// Hash the serial number and the disk extents of a fixed drive into *pHash.
bool __cdecl FUN_006b82a0(char driveLetter, uint32_t* pHash)
{
    bool ok = false;
    char root[4] = "X:\\";
    root[0] = driveLetter;
    if (GetDriveTypeA(root) != 3)            // DRIVE_FIXED
        return false;

    char path[0x104];
    sprintf(path, "%c:\\", (int)driveLetter);

    char     volumeName[0x104];
    char     fsName[0x104];
    uint32_t serial = 0;
    uint32_t maxComponent = 0;
    uint32_t fsFlags = 0;
    if (!GetVolumeInformationA(path, volumeName, 0x104, &serial, &maxComponent,
                               &fsFlags, fsName, 0x104))
        return false;

    *pHash = HashBytes(&serial, 4, *pHash);

    char device[0x104];
    sprintf(device, "\\\\.\\%c:", (int)driveLetter);
    HANDLE h = CreateFileA(device, 0, 3, 0, 3, 0, 0);
    if (h == (HANDLE)-1)
        return false;

    VolumeDiskExtents extents;
    uint32_t bytesReturned = 0;
    if (DeviceIoControl(h, 0x560000u, 0, 0, &extents, 0x400, &bytesReturned, 0)) {
        for (uint32_t i = 0; i < extents.mNumberOfDiskExtents; i++) {
            DiskExtent* e = &extents.mExtents[i];
            *pHash = HashBytes(&extents.mNumberOfDiskExtents, 4, *pHash);
            *pHash = HashBytes(&e->mDiskNumber, 8, *pHash);
            *pHash = HashBytes(&e->mStartingOffset, 8, *pHash);
        }
        ok = true;
    }
    CloseHandle(h);
    return ok;
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
