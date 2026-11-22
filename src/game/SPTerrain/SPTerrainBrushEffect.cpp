// src/game/SPTerrain/SPTerrainBrushEffect.cpp -- migrated from slice(s) s00f4ef20, s00f4d9c0 by tools/migrate/rewrite.py
// Object file: SPTerrain/SPTerrainBrushEffect.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "EA/Random/RandomLinearCongruential.h"
#include <math.h>
#include "SP/cTerrainMapSet.h"
#include "SP/cTerrainSphere.h"

// ---- items of slice s00f4ef20 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
void   Sub_f4d9c0();                                          // 0x00f4d9c0
}
namespace SP {
struct cTerrainBrushDescription;
}
namespace SP {
class cTerrainBrushEffect {
public:
    virtual void Initialize(void*, void*, void*);   // +0x00
    virtual void Dispose();                         // +0x04
    virtual void Start(int hardStart);              // +0x08
    virtual void Stop(int hardStop);                // +0x0c
    virtual int  IsRunning();                       // +0x10
    virtual void ApplyEffect(float, float, void*);  // +0x14

    int   mRefCount;                                // +0x04
    int   mRefCountPad;                             // +0x08
    cTerrainBrushDescription* mDesc;                // +0x0c
    char  mActive;                                  // +0x10
};
}
// ---- items of slice s00f4ef20 end

// @ 0x00f4d9c0
inline void* operator new(unsigned int, void* p)
{ return p; }

// @ 0x00f4ef20
void SP::cTerrainBrushEffect::Stop(int hardStop)
{
    if (mActive) {
        SP::cTerrainBrushDescription* d = mDesc;
        mActive = 0;
        if (*(char*)((char*)d + 0xec))
            SP::Sub_f4d9c0();
    }
    (void)hardStop;
}
