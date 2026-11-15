// src/game/SPMovie/movietimer.cpp -- migrated from slice(s) s00fcb210 by tools/migrate/rewrite.py
// Object file: SPMovie/movietimer.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include <intrin.h>
#pragma intrinsic(__rdtsc)

// ---- items of slice s00fcb210 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace rw {
namespace core {
namespace timer {
class Stopwatch
{ public:
    void*   vftable;     // +0x00
    void*   mCallback;   // +0x04
    int32_t mUnits;      // +0x08
    int32_t pad_0c;
    int32_t mStartLo;    // +0x10
    int32_t mStartHi;    // +0x14
    int32_t mElapsedLo;  // +0x18
    int32_t mElapsedHi;  // +0x1c
    float   mScale;      // +0x20

    virtual void Destroy(int a);        // +0x00 (deleting-ish dtor)
};
}
}
}
namespace rw {
namespace core {
namespace timer {
Stopwatch* Stopwatch_Ctor(Stopwatch* mem, int units, int a);   // 0x011e82d0 __thiscall
}
}
}
using rw::core::timer::Stopwatch;
struct ICoreAllocator
{
    virtual void  v00();                                   // +0x00
    virtual void* Alloc(uint32_t size, const char* name, int a,
                        int b, int c);                     // +0x04
    virtual void  v08();                                   // +0x08
    virtual void  Free(void* p, int a);                    // +0x0c
};
namespace rw {
namespace movie {
struct IMovieTimerCallback
{
    virtual void  v0();          // +0x00
    virtual void  v1();          // +0x04
    virtual void  v2();          // +0x08
    virtual float v3();          // +0x0c  (returns elapsed seconds)
};
}
}
namespace rw {
namespace movie {
class MovieTimer
{ public:
    ICoreAllocator* mAllocator;   // +0x00
    Stopwatch*      mStopwatch;   // +0x04
    IMovieTimerCallback* mCallback; // +0x08

    MovieTimer* Ctor(ICoreAllocator* allocator);   // 0x00fcc0b0
    void  Destroy();                               // 0x00fcc100
    void  Update();                                // 0x00fcc150
    void  Sync();                                  // 0x00fcc180
    float Elapsed();                               // 0x00fcc190
};
}
}
// ---- items of slice s00fcb210 end

// @ 0x00fcc0b0
rw::movie::MovieTimer* rw::movie::MovieTimer::Ctor(ICoreAllocator* allocator)
{
    mAllocator = allocator;
    Stopwatch* sw = (Stopwatch*)allocator->Alloc(0x28, "Stopwatch object", 1, 4, 0);
    mStopwatch = sw;
    if (sw != 0)
    {
        sw = rw::core::timer::Stopwatch_Ctor(sw, 4, 0);
        mStopwatch = sw;
        mCallback = 0;
        return this;
    }
    mStopwatch = 0;
    mCallback = 0;
    return this;
}
