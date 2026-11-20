// addresses retail relocates here, named so the build relocates them too
extern "C" char g_13eb938[];
extern "C" char g_13ec458[];
extern "C" char g_1473478[];
extern "C" char g_147349c[];

#include "types.h"
#include <intrin.h>

struct RefCountedObject {
    virtual void v0();
    virtual void Release();
};

struct PlanetVector {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;

    void Destroy(); // 0x00ad92d0
};

struct CelestialVector {
    void* mpBegin;
    void* mpEnd;
    void* mpCapacity;

    void Destroy(); // 0x00ae6970
};

struct ModelVector {
    void** mpBegin;
    void** mpEnd;
    void** mpCapacity;

    void DoDestroyValues(void** first, void** last); // 0x005f3680
    __forceinline void DestroyContents()
{
    DoDestroyValues(mpBegin, mpEnd);
}
};

void __cdecl FreeVectorMemory(void* p); // 0x00f47380

namespace Simulator {

struct cSolarSystem {
    void* mpVtable0;
    unsigned int mRefCount;
    void* mpVtable1;
    void* mpOwnerStar;

    PlanetVector mPlanets;         // +0x10
    unsigned int mPad1C;
    unsigned int mPad20;

    CelestialVector mCelestialBodies; // +0x24
    unsigned int mPad30;
    unsigned int mPad34;

    RefCountedObject* mpStar1; // +0x38
    RefCountedObject* mpStar2; // +0x3C

    ModelVector mModels;       // +0x40

    void Destroy();
};

// @ 0x00c84be0
void cSolarSystem::Destroy()
{
ModelVector& models = mModels;

_ReadWriteBarrier();

mpVtable0 = (void*)g_147349c;
mpVtable1 = (void*)g_1473478;

_ReadWriteBarrier();

models.DoDestroyValues(models.mpBegin, models.mpEnd);

void** begin = models.mpBegin;

    if (begin && *((int*)begin - 1) != 0) {
        FreeVectorMemory(begin);
    }

    if (mpStar2) {
        mpStar2->Release();
    }

    if (mpStar1) {
        mpStar1->Release();
    }

    mCelestialBodies.Destroy();
    mPlanets.Destroy();

    mpVtable1 = (void*)g_13eb938;
    mpVtable0 = (void*)g_13ec458;
}

} // namespace Simulator
