// src/game/SPGonzago/SPSpaceColonyTuning.cpp -- migrated from slice(s) s010297e0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPSpaceColonyTuning.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cSPCreatureBase.h"
#include "SP/cGameNounManager.h"
#include "SP/cPlanetModel.h"
#include "SP/cEmpire.h"
#include "SP/cRelationshipManager.h"
#include "SP/cSPGameDataUFO.h"
#include "SP/cSPMission.h"
#include "SP/cStarManager.h"

// ---- items of slice s010297e0 begin (TODO(rewrite): local stubs, replace by canonical classes)
typedef unsigned int uint;
struct IUnk { virtual int AddRef(); virtual int Release(); };   // +4 = Release
struct PropertyMgr {
virtual void m00();
virtual void m01();
virtual void m02();
virtual void m03();
virtual void m04();
virtual void m05();
virtual void m06();
virtual void m07();
virtual void m08();
virtual void m09();
virtual void m10();
    virtual void Unregister(uint a, uint b, IUnk** slot);   // +0x2c
};
void* PropertyManager();                                    // 0x0067de30
struct C010297e0 {
    char pad[8];
    IUnk* mRef;
    void f();
};
// ---- items of slice s010297e0 end

// @ 0x010297e0
void C010297e0::f()
{
    PropertyMgr* pm = (PropertyMgr*)PropertyManager();
    IUnk* old = mRef;
    if (old) {
        mRef = 0;
        old->Release();
    }
    pm->Unregister(0x7436b54a, 0x2ae0c7e, &mRef);
}
