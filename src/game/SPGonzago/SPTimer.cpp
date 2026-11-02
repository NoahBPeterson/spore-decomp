// src/game/SPGonzago/SPTimer.cpp -- migrated from slice(s) s00bc2570 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPTimer.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPTimer.h"
#include "SP/cPlanet.h"
#pragma warning(disable: 4100)
#include <string.h>

// ---- items of slice s00bc2570 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef uint64_t (__cdecl* SPTimeFn)();
struct cSPTimer {
    void*   mVtbl;       // +0x00
    uint32_t mUnk4;      // +0x04
    uint64_t mElapsed;   // +0x08
    uint64_t mBase;      // +0x10
    uint8_t mRunning;    // +0x18
    uint8_t pad_19[3];
    SPTimeFn mGetTime;   // +0x1c

    void      Start();
    void      Stop();
    void      Restart();
    void      FUN_00bc3150(uint64_t delta);
    void      FUN_00bc3170();
    uint64_t  GetElapsedTime();
    cSPTimer* FUN_00bc31c0(SPTimeFn fn);
};
// ---- items of slice s00bc2570 end

// @ 0x00bc30f0
void cSPTimer::Start()
{
    if (!mRunning) {
        mBase = mGetTime();
        mRunning = true;
    }
}

// @ 0x00bc3110
void cSPTimer::Stop()
{
    if (mRunning) {
        uint64_t now = mGetTime();
        mRunning = false;
        mElapsed += now - mBase;
    }
}

// @ 0x00bc3130
void cSPTimer::Restart()
{
    mBase = mGetTime();
    mElapsed = 0;
    mRunning = true;
}

// @ 0x00bc3150
void cSPTimer::FUN_00bc3150(uint64_t delta)
{
    if (mRunning)
        mBase += delta;
}

// @ 0x00bc3170
void cSPTimer::FUN_00bc3170()
{
    mBase = 0;
    mElapsed = 0;
    mRunning = false;
}

// @ 0x00bc3190
uint64_t cSPTimer::GetElapsedTime()
{
    if (mRunning) {
        uint64_t now = mGetTime();
        return mElapsed + (now - mBase);
    }
    return mElapsed;
}
