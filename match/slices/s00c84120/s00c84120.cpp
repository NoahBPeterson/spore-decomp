// Slice s00c84120 -- Simulator::cSolarSystem (partial).
// Module flags: /O2 /MD /Gy /TP /arch:SSE /fp:fast
#include "types.h"

namespace Simulator {

struct cPtrVector {
    void* mpBegin;                                           // +0x00
    void* mpEnd;                                             // +0x04
    void* mpCapacity;                                        // +0x08
};

struct cSolarSystem {
    void*       mpVtable0;                                   // +0x00
    uint32_t    mRefCount;                                   // +0x04
    void*       mpVtable1;                                   // +0x08
    void*       mpOwnerStar;                                 // +0x0c
    cPtrVector  mPlanets;                                    // +0x10
    uint32_t    mPad1c;                                      // +0x1c
    uint32_t    mPad20;                                      // +0x20
    cPtrVector  mCelestialBodies;                            // +0x24
    uint32_t    mPad30;                                      // +0x30
    uint32_t    mPad34;                                      // +0x34
    cPtrVector  mModels;                                     // +0x38
    void*       mpStar1;                                     // +0x44
    void*       mpStar2;                                     // +0x48

    cSolarSystem();
};

// @ 0x00c84b50
cSolarSystem::cSolarSystem()
{
    mRefCount = 0;
    mpVtable1 = (void*)0x01444434;
    mpVtable0 = (void*)0x0147349c;
    mpVtable1 = (void*)0x01473478;
    mpOwnerStar = 0;
    mPlanets.mpBegin = 0;
    mPlanets.mpEnd = 0;
    mPlanets.mpCapacity = 0;
    mCelestialBodies.mpBegin = 0;
    mCelestialBodies.mpEnd = 0;
    mCelestialBodies.mpCapacity = 0;
    mModels.mpBegin = 0;
    mModels.mpEnd = 0;
    mModels.mpCapacity = 0;
    mpStar1 = 0;
    mpStar2 = 0;
}

} // namespace Simulator
