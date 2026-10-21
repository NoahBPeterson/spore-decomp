// src/game/UTFSpore_Win32/EAStopwatch.cpp -- migrated from slice(s) s00939a60 by tools/migrate/rewrite.py
// Object file: UTFSpore_Win32/EAStopwatch.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Stopwatch.h"
#include "EA/LimitStopwatch.h"
#include "SP/cDirectPropertyList.h"

// unnamed retail callees and globals (address in the comment)
extern "C" unsigned short _byteswap_ushort(unsigned short);
extern "C" unsigned long  _byteswap_ulong(unsigned long);
extern "C" unsigned __int64 __rdtsc(void);
extern "C" uint64_t mnStopwatchFrequency;                    // 0x154eae8
extern "C" uint64_t mnStopwatchCycleReadingOverhead;         // 0x16699a0
extern "C" float kfStopwatchRoundConstant;                   // 0x143eaa8
extern "C" float mfStopwatchCyclesToNanosecondsCoefficient;  // 0x1669958
extern "C" float mfStopwatchCyclesToMicrosecondsCoefficient; // 0x1669974
extern "C" float mfStopwatchCyclesToMillisecondsCoefficient; // 0x166996c
extern "C" float mfStopwatchCyclesToSecondsCoefficient;      // 0x1669980
extern "C" float mfStopwatchCyclesToMinutesCoefficient;      // 0x166995c
#pragma intrinsic(_byteswap_ushort, _byteswap_ulong)
#pragma intrinsic(__rdtsc)

// ---- items of slice s00939a60 begin (TODO(rewrite): local stubs, replace by canonical classes)
__declspec(dllimport) int __stdcall QueryPerformanceCounter(int64_t* p);
extern "C" unsigned __int64 __rdtsc(void);
extern "C" uint64_t mnStopwatchFrequency;                    // 0x154eae8
extern "C" uint64_t mnStopwatchCycleReadingOverhead;         // 0x16699a0
extern "C" float kfStopwatchRoundConstant;                   // 0x143eaa8
extern "C" float mfStopwatchCyclesToNanosecondsCoefficient;  // 0x1669958
extern "C" float mfStopwatchCyclesToMicrosecondsCoefficient; // 0x1669974
extern "C" float mfStopwatchCyclesToMillisecondsCoefficient; // 0x166996c
extern "C" float mfStopwatchCyclesToSecondsCoefficient;      // 0x1669980
extern "C" float mfStopwatchCyclesToMinutesCoefficient;      // 0x166995c
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
class cSPUILayerManager { public:
    char    pad00[0x14];
    float   mfCoeff;    // 0x14
    int64_t mnTime;     // 0x18
    int64_t GetDelta();
};
struct cDirectPropertyList {
    void*   mpVtbl;      // 0x00
    int32_t mnRefCount;  // 0x04
    int64_t mnAccum;     // 0x08
    int32_t mGroup;      // 0x10
    void SetBoolProperty();
};
// ---- items of slice s00939a60 end

// unnamed retail callees and globals that name local stubs (address in the comment)
extern "C" uint64_t mnCPUFrequency;                          // 0x154eaf0

// @ 0x0093a1a0
void EA::Stopwatch::SetUnits(int units)
{
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

// @ 0x0093a2e0
void cDirectPropertyList::SetBoolProperty()
{
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

// @ 0x0093a380
void Stopwatch::SetElapsedCycles(int64_t cycles)
{
    mnTotalElapsedTime = (int64_t)(cycles / mfStopwatchCyclesToUnitsCoefficient + kfStopwatchRoundConstant);
}

// @ 0x0093a420
float GetCyclesToUnitsCoefficient(int units)
{
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
uint64_t GetStopwatchFrequency()
{
    return mnStopwatchFrequency;
}

// @ 0x0093a480
void EA::LimitStopwatch::SetTimeLimit(unsigned int ms, bool start)
{
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

// @ 0x0093a510
int64_t cSPUILayerManager::GetDelta()
{
    int64_t now;
    QueryPerformanceCounter(&now);
    return (int64_t)((double)(mnTime - now) * mfCoeff);
}

// @ 0x0093a560
EA::Stopwatch::Stopwatch(int units, bool start)
{
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
int64_t Stopwatch::GetElapsedTime()
{
    return (int64_t)(GetElapsedTimeFloat() * mfStopwatchCyclesToUnitsCoefficient + kfStopwatchRoundConstant);
}
