// Slice s00939a60 -- EA::Stopwatch / EA::LimitStopwatch + EA::IO stream read helpers.
// Module flags: /O2 /MD /Gy /EHsc /TP /arch:SSE
#include "types.h"

extern "C" unsigned short _byteswap_ushort(unsigned short);
extern "C" unsigned long  _byteswap_ulong(unsigned long);
extern "C" uint64_t ByteSwap64(uint32_t lo, uint32_t hi);   // 0x008de020
#pragma intrinsic(_byteswap_ushort, _byteswap_ulong)

__declspec(dllimport) int __stdcall QueryPerformanceCounter(int64_t* p);
__declspec(dllimport) int __stdcall QueryPerformanceFrequency(int64_t* p);
__declspec(dllimport) void* __stdcall GetCurrentProcess(void);
__declspec(dllimport) unsigned __stdcall GetPriorityClass(void* h);
__declspec(dllimport) void* __stdcall GetCurrentThread(void);
__declspec(dllimport) int __stdcall GetThreadPriority(void* h);
__declspec(dllimport) int __stdcall SetPriorityClass(void* h, unsigned c);
__declspec(dllimport) int __stdcall SetThreadPriority(void* h, int p);
__declspec(dllimport) unsigned __stdcall SleepEx(unsigned ms, int alertable);
extern "C" unsigned __int64 __rdtsc(void);
#pragma intrinsic(__rdtsc)

__declspec(dllimport) wchar_t* __cdecl wcschr(const wchar_t* s, wchar_t c);

// swscanf dispatch pointer (installed at startup from the swscanf import)
typedef int (__cdecl* ScanfFn)(const wchar_t*, const wchar_t*, ...);
extern "C" ScanfFn gpScanfFn;                                // 0x166994c

// ------------------------------------------------------------------ globals
extern "C" uint64_t mnStopwatchFrequency;                    // 0x154eae8
extern "C" uint64_t mnCPUFrequency;                          // 0x154eaf0
extern "C" uint64_t mnStopwatchCycleReadingOverhead;         // 0x16699a0
extern "C" float kfStopwatchRoundConstant;                   // 0x143eaa8
extern "C" float mfStopwatchCyclesToNanosecondsCoefficient;  // 0x1669958
extern "C" float mfStopwatchCyclesToMicrosecondsCoefficient; // 0x1669974
extern "C" float mfStopwatchCyclesToMillisecondsCoefficient; // 0x166996c
extern "C" float mfStopwatchCyclesToSecondsCoefficient;      // 0x1669980
extern "C" float mfStopwatchCyclesToMinutesCoefficient;      // 0x166995c
// inverse (units -> cycles) coefficients, same block as above
extern "C" float mfStopwatchUnitsToCyclesNanoseconds;        // 0x1669970
extern "C" float mfStopwatchUnitsToCyclesMicroseconds;       // 0x1669988
extern "C" float mfStopwatchUnitsToCyclesMilliseconds;       // 0x166998c
extern "C" float mfStopwatchUnitsToCyclesSeconds;            // 0x1669960
extern "C" float mfStopwatchUnitsToCyclesMinutes;            // 0x166999c
// CPU (rdtsc) coefficient block
extern "C" float mfCPUCyclesToNanosecondsCoefficient;        // 0x1669950
extern "C" float mfCPUCyclesToMicrosecondsCoefficient;       // 0x1669968
extern "C" float mfCPUCyclesToMillisecondsCoefficient;       // 0x1669954
extern "C" float mfCPUCyclesToSecondsCoefficient;            // 0x166997c
extern "C" float mfCPUCyclesToMinutesCoefficient;            // 0x1669994
extern "C" float mfCPUUnitsToCyclesNanoseconds;              // 0x1669978
extern "C" float mfCPUUnitsToCyclesMicroseconds;             // 0x1669984
extern "C" float mfCPUUnitsToCyclesMilliseconds;             // 0x1669990
extern "C" float mfCPUUnitsToCyclesSeconds;                  // 0x1669998
extern "C" float mfCPUUnitsToCyclesMinutes;                  // 0x1669964
extern "C" uint64_t mnCPUCycleReadingOverhead;               // 0x16699a8

// ------------------------------------------------------------------ Stopwatch
struct Stopwatch {
    uint64_t mnStartTime;                         // 0x00
    uint64_t mnTotalElapsedTime;                  // 0x08
    int      mnUnits;                             // 0x10
    float    mfStopwatchCyclesToUnitsCoefficient; // 0x14

    Stopwatch(int units, bool start);
    void SetUnits(int units);
    int64_t GetElapsedTimeFloat();
    int64_t GetElapsedTime();
    void SetElapsedCycles(int64_t cycles);
};
struct LimitStopwatch : Stopwatch {
    uint64_t mnEndTime;   // 0x18
    void SetTimeLimit(uint32_t ms, bool start);
};

// @ 0x0093a1a0  (complete, near miss)
void Stopwatch::SetUnits(int units) {
    mnUnits = units;
    mfStopwatchCyclesToUnitsCoefficient = 1.0f;
    switch (units) {
    case 0:
        break;
    case 1:
        mfStopwatchCyclesToUnitsCoefficient = (float)mnStopwatchFrequency / (float)mnCPUFrequency;
        break;
    case 2:
        mfStopwatchCyclesToUnitsCoefficient = mfStopwatchCyclesToNanosecondsCoefficient;
        break;
    case 3:
        mfStopwatchCyclesToUnitsCoefficient = mfStopwatchCyclesToMicrosecondsCoefficient;
        break;
    case 4:
        mfStopwatchCyclesToUnitsCoefficient = mfStopwatchCyclesToMillisecondsCoefficient;
        break;
    case 5:
        mfStopwatchCyclesToUnitsCoefficient = mfStopwatchCyclesToSecondsCoefficient;
        break;
    case 6:
        mfStopwatchCyclesToUnitsCoefficient = mfStopwatchCyclesToMinutesCoefficient;
        break;
    }
}

// @ 0x0093a380
void Stopwatch::SetElapsedCycles(int64_t cycles) {
    mnTotalElapsedTime = (int64_t)(cycles / mfStopwatchCyclesToUnitsCoefficient + kfStopwatchRoundConstant);
}

// @ 0x0093a3a0  (complete, 4-byte near miss: half-load order)
int64_t Stopwatch::GetElapsedTimeFloat() {
    int64_t elapsed = mnTotalElapsedTime;
    if (mnStartTime != 0) {
        int64_t now;
        if (mnUnits == 1) {
            now = __rdtsc();
        } else {
            QueryPerformanceCounter(&now);
        }
        uint64_t cycles = (uint64_t)(now - mnStartTime);
        if (cycles > mnStopwatchCycleReadingOverhead)
            elapsed += (int64_t)(cycles - mnStopwatchCycleReadingOverhead);
        else
            elapsed += 1;
    }
    return elapsed;
}

// @ 0x0093a560
Stopwatch::Stopwatch(int units, bool start) {
    mnStartTime = 0;
    mnTotalElapsedTime = 0;
    mnUnits = 0;
    mfStopwatchCyclesToUnitsCoefficient = 1.0f;
    SetUnits(units);
    if (start && mnStartTime == 0) {
        if (mnUnits == 1) {
            mnStartTime = __rdtsc();
            return;
        }
        int64_t li;
        QueryPerformanceCounter(&li);
        mnStartTime = li;
    }
}

// @ 0x0093a5e0
int64_t Stopwatch::GetElapsedTime() {
    return (int64_t)(GetElapsedTimeFloat() * mfStopwatchCyclesToUnitsCoefficient + kfStopwatchRoundConstant);
}

// @ 0x0093a480  (complete, near miss: x87 rounding sequence)
void LimitStopwatch::SetTimeLimit(uint32_t ms, bool start) {
    int64_t now;
    QueryPerformanceCounter(&now);
    int64_t ticks = (int64_t)((double)ms / (double)mfStopwatchCyclesToUnitsCoefficient);
    mnEndTime = ticks + now;
    if (start && mnStartTime == 0) {
        if (mnUnits == 1) {
            mnStartTime = __rdtsc();
            return;
        }
        int64_t li;
        QueryPerformanceCounter(&li);
        mnStartTime = li;
    }
}

// @ 0x0093a420
float GetCyclesToUnitsCoefficient(int units) {
    switch (units) {
    case 2: return mfStopwatchCyclesToNanosecondsCoefficient;
    case 3: return mfStopwatchCyclesToMicrosecondsCoefficient;
    case 4: return mfStopwatchCyclesToMillisecondsCoefficient;
    case 5: return mfStopwatchCyclesToSecondsCoefficient;
    case 6: return mfStopwatchCyclesToMinutesCoefficient;
    default: return 1.0f;
    }
}

// @ 0x0093a470
uint64_t GetStopwatchFrequency() {
    return mnStopwatchFrequency;
}

// ---------------------------------------------------------------- IO streams
class IOStream {
public:
    virtual void v00();
    virtual void v04();
    virtual void v08();
    virtual void v0c();
    virtual void v10();
    virtual int  v14();
    virtual void v18();
    virtual unsigned v1c();
    virtual void v20();
    virtual void* v24(int);
    virtual void v28(int, int);
    virtual unsigned v2c();
    virtual int  v30(void* buf, int n);
    virtual void v34();
    virtual bool v38(void* buf, int n);
};

// @ 0x0093a6c0
bool WriteExact(IOStream* s, void* buf, int n) {
    if (s->v14())
        return false;
    bool b = s->v30(buf, n) == n;
    return b;
}

// @ 0x0093a700
bool ReadUInt16(IOStream* s, unsigned short* buf, int count, int bigEndian) {
    if (bigEndian != 1)
        s->v10();
    if (s->v14())
        return false;
    bool ok = false;
    if (s->v30(buf, count * 2) == count * 2) {
        if (bigEndian != 1) {
            while (count--) {
                *buf = _byteswap_ushort(*buf);
                ++buf;
            }
        }
        ok = true;
    }
    return ok;
}

// @ 0x0093a780
bool ReadInt32(IOStream* s, uint32_t* buf, int count, int bigEndian) {
    if (bigEndian != 1)
        s->v10();
    if (s->v14())
        return false;
    bool ok = false;
    if (s->v30(buf, count * 4) == count * 4) {
        if (bigEndian != 1) {
            while (count--) {
                *buf = _byteswap_ulong(*buf);
                ++buf;
            }
        }
        ok = true;
    }
    return ok;
}

// @ 0x0093a800
bool ReadUInt64(IOStream* s, uint64_t* buf, int count, int bigEndian) {
    if (bigEndian != 1)
        s->v10();
    if (s->v14())
        return false;
    bool ok = false;
    if (s->v30(buf, count * 8) == count * 8) {
        if (bigEndian != 1) {
            while (count--) {
                uint32_t* p = (uint32_t*)buf;
                *(uint64_t*)buf = ByteSwap64(p[0], p[1]);
                ++buf;
            }
        }
        ok = true;
    }
    return ok;
}

// @ 0x0093a890
bool HasRoom(IOStream* s, int a, int b) {
    return (unsigned)(a * b) <= s->v2c();
}

// @ 0x0093a9a0
bool StreamWrite(IOStream* s, int a, int b) {
    if (s->v14())
        return false;
    return s->v38((void*)a, b);
}

// @ 0x0093a8b0  (complete, near miss: buffered-line state machine)
unsigned ReadLine(IOStream* s, char* buf) {
    if (s->v14())
        return 0;
    int n = 0;
    unsigned len = 0;
    void* alloc = 0;
    if (buf == 0)
        alloc = s->v24(0);
    char ch = 0;
    if (s->v30(&ch, 1) == 1) {
        do {
            ++n;
            if (ch == '\r' || ch == '\n') {
                char ch2 = ch;
                int r = 1;
                if (ch == '\r')
                    r = s->v30(&ch2, 1);
                if (r == 1 && ch2 != '\n')
                    s->v28(-1, 1);
                goto done;
            }
            if (buf != 0 && len < 0xffffffffu)
                *buf++ = ch;
            ++len;
        } while (s->v30(&ch, 1) == 1);
        if (n != 0)
            goto done;
    }
    len = 0xfffffffe;
done:
    if (buf == 0) {
        s->v28((int)alloc, 0);
        return len;
    }
    *buf = 0;
    return len;
}

// @ 0x0093a510  (complete, near miss: inline fistp vs _ftol2)
class cSPUILayerManager { public:
    char    pad00[0x14];
    float   mfCoeff;    // 0x14
    int64_t mnTime;     // 0x18
    int64_t GetDelta();
};
int64_t cSPUILayerManager::GetDelta() {
    int64_t now;
    QueryPerformanceCounter(&now);
    return (int64_t)((double)(mnTime - now) * mfCoeff);
}

// @ 0x0093a2e0  (complete, near miss: timing/refcount bookkeeping)
struct cDirectPropertyList {
    void*   mpVtbl;      // 0x00
    int32_t mnRefCount;  // 0x04
    int64_t mnAccum;     // 0x08
    int32_t mGroup;      // 0x10
    void SetBoolProperty();
};
void cDirectPropertyList::SetBoolProperty() {
    if (mpVtbl != 0 || mnRefCount != 0) {
        int64_t now = 0;
        if (mGroup == 1)
            now = (int64_t)__rdtsc();
        else
            QueryPerformanceCounter(&now);
        uint64_t elapsed = (uint64_t)(now - mnAccum);
        if (elapsed > mnStopwatchCycleReadingOverhead) {
            uint64_t c = elapsed - mnStopwatchCycleReadingOverhead;
            uint64_t old = (uint64_t)mnAccum;
            mnAccum = (int64_t)(old + c);
            mpVtbl = 0;
            mnRefCount = 0;
        } else {
            uint64_t old = (uint64_t)mnAccum;
            mnAccum = (int64_t)(old + 1);
            mpVtbl = 0;
            mnRefCount = 0;
        }
    }
}

// @ 0x0093a610
int StreamCopy(IOStream* src, IOStream* dst, unsigned count) {
    uint32_t buf[0x200];
    unsigned size = src->v1c();
    if (size == 0xffffffffu) {
        count = size;
    } else if (count > size) {
        count = size;
    }
    unsigned total = count;
    while (total != 0) {
        unsigned chunk = total >= 0x800 ? 0x800 : total;
        int r = src->v30(buf, chunk);
        if (r == -1 || !dst->v38(buf, r))
            return -1;
        if (r == 0)
            break;
        total -= r;
    }
    return (int)(count - total);
}

// @ 0x00939a60
// EAStdC wide-character sscanf core. pFormat is scanned for the argument-
// consuming conversion specifiers (capped at 20); the matching count of raw
// varargs is copied out of the va_list pointer and forwarded to the CRT
// swscanf entry held in gpScanfFn (0x166994c). Only up to 10 arguments are
// forwarded; anything else returns 0.
int Vsscanf16(const wchar_t* pString, const wchar_t* pFormat, uint32_t* arguments) {
    uint32_t args[16];
    int count = 0;
    const wchar_t* p = wcschr(pFormat, L'%');
    while (p != 0) {
        if (*p != L'%')
            break;
        if (count >= 20)
            break;
        switch (p[1]) {
        case L'%':
            ++p;
            break;
        case L' ':
        case L'#':
        case L'+':
        case L'-':
            if (p[2] != L'*')
                ++count;
            break;
        case L'*':
            break;
        default:
            ++count;
            break;
        }
        p = wcschr(p + 1, L'%');
    }

    for (int i = 0; i < count; ++i)
        args[i] = arguments[i];

    switch (count) {
    case 0:
        return gpScanfFn(pString, pFormat);
    case 1:
        return gpScanfFn(pString, pFormat, args[0]);
    case 2:
        return gpScanfFn(pString, pFormat, args[0], args[1]);
    case 3:
        return gpScanfFn(pString, pFormat, args[0], args[1], args[2]);
    case 4:
        return gpScanfFn(pString, pFormat, args[0], args[1], args[2], args[3]);
    case 5:
        return gpScanfFn(pString, pFormat, args[0], args[1], args[2], args[3], args[4]);
    case 6:
        return gpScanfFn(pString, pFormat, args[0], args[1], args[2], args[3], args[4], args[5]);
    case 7:
        return gpScanfFn(pString, pFormat, args[0], args[1], args[2], args[3], args[4], args[5], args[6]);
    case 8:
        return gpScanfFn(pString, pFormat, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7]);
    case 9:
        return gpScanfFn(pString, pFormat, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8]);
    case 10:
        return gpScanfFn(pString, pFormat, args[0], args[1], args[2], args[3], args[4], args[5], args[6], args[7], args[8], args[9]);
    default:
        return 0;
    }
}

// @ 0x00939d40
// EA::Stopwatch module initialiser: calibrates the CPU (rdtsc) frequency, then
// derives the cycles<->time coefficients for both the QPC and rdtsc clocks.
void GetCPUFrequency() {
    if (mnStopwatchFrequency >= 2)
        return;

    void* hProcess = GetCurrentProcess();
    unsigned prioClass = GetPriorityClass(hProcess);
    void* hThread = GetCurrentThread();
    int threadPrio = GetThreadPriority(hThread);
    SetPriorityClass(hProcess, 0x100);
    SetThreadPriority(hThread, 0xf);

    mnCPUFrequency = 0;
    for (int i = 0; i < 5; ++i) {
        uint64_t qpc;
        QueryPerformanceCounter((int64_t*)&qpc);
        uint64_t tsc = __rdtsc();
        double ratio = (double)tsc / (double)qpc;
        if (ratio > 0.98 && ratio < 1.02) {
            QueryPerformanceFrequency((int64_t*)&mnCPUFrequency);
            break;
        }
    }

    if (mnCPUFrequency == 0) {
        uint64_t qpcFreq;
        QueryPerformanceFrequency((int64_t*)&qpcFreq);
        uint64_t qpc0;
        QueryPerformanceCounter((int64_t*)&qpc0);
        uint64_t tsc0 = __rdtsc();
        double elapsed;
        uint64_t tsc1;
        do {
            SleepEx(50, 1);
            uint64_t qpc1;
            QueryPerformanceCounter((int64_t*)&qpc1);
            tsc1 = __rdtsc();
            elapsed = (double)(qpc1 - qpc0) / (double)qpcFreq;
        } while (elapsed < 0.25);
        mnCPUFrequency = (uint64_t)((double)(tsc1 - tsc0) / elapsed);
    }

    QueryPerformanceFrequency((int64_t*)&mnStopwatchFrequency);
    SetPriorityClass(hProcess, prioClass);
    SetThreadPriority(hThread, threadPrio);

    {
        float base = (float)(1.0 / (double)mnStopwatchFrequency);
        float nano = base * 1e9f;
        float micro = base * 1e6f;
        float milli = base * 1e3f;
        float secs = base;
        float mins = base * 0.016666668f;
        mfStopwatchCyclesToNanosecondsCoefficient = nano;
        mfStopwatchCyclesToMicrosecondsCoefficient = micro;
        mfStopwatchCyclesToMillisecondsCoefficient = milli;
        mfStopwatchCyclesToSecondsCoefficient = secs;
        mfStopwatchCyclesToMinutesCoefficient = mins;
        mfStopwatchUnitsToCyclesNanoseconds = 1.0f / nano;
        mfStopwatchUnitsToCyclesMicroseconds = 1.0f / micro;
        mfStopwatchUnitsToCyclesMilliseconds = 1.0f / milli;
        mfStopwatchUnitsToCyclesSeconds = 1.0f / secs;
        mfStopwatchUnitsToCyclesMinutes = 1.0f / mins;
    }

    uint64_t qpcOverhead = 0xffffffffffffffffull;
    for (int j = 0; j < 8; ++j) {
        uint64_t a, b;
        QueryPerformanceCounter((int64_t*)&a);
        QueryPerformanceCounter((int64_t*)&b);
        uint64_t d = b - a;
        if (d < qpcOverhead)
            qpcOverhead = d;
    }
    mnStopwatchCycleReadingOverhead = qpcOverhead;

    {
        float base = (float)(1.0 / (double)mnCPUFrequency);
        float nano = base * 1e9f;
        float micro = base * 1e6f;
        float milli = base * 1e3f;
        float secs = base;
        float mins = base * 0.016666668f;
        mfCPUCyclesToNanosecondsCoefficient = nano;
        mfCPUCyclesToMicrosecondsCoefficient = micro;
        mfCPUCyclesToMillisecondsCoefficient = milli;
        mfCPUCyclesToSecondsCoefficient = secs;
        mfCPUCyclesToMinutesCoefficient = mins;
        mfCPUUnitsToCyclesNanoseconds = 1.0f / nano;
        mfCPUUnitsToCyclesMicroseconds = 1.0f / micro;
        mfCPUUnitsToCyclesMilliseconds = 1.0f / milli;
        mfCPUUnitsToCyclesSeconds = 1.0f / secs;
        mfCPUUnitsToCyclesMinutes = 1.0f / mins;
    }

    uint64_t tscOverhead = 0xffffffffffffffffull;
    for (int j = 0; j < 8; ++j) {
        uint64_t a = __rdtsc();
        uint64_t b = __rdtsc();
        uint64_t d = b - a;
        if (d < tscOverhead)
            tscOverhead = d;
    }
    mnCPUCycleReadingOverhead = tscOverhead;
}
