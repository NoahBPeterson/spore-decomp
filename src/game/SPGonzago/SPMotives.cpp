// src/game/SPGonzago/SPMotives.cpp -- migrated from slice(s) s00b70820 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPMotives.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cPropertyManager.h"
#include "SP/cTerrainSphere.h"

// ---- items of slice s00b70820 begin (TODO(rewrite): local stubs, replace by canonical classes)
struct cTuning_b708d0 {
    float f00, f04, f08, f0c, f10, f14, f18, f1c, f20, f24, f28, f2c, f30, f34, f38, f3c;
    float f40, f44, f48, f4c, f50, f54, f58, f5c, f60, f64;
    uint32_t u68;
    float f6c;
    uint32_t u70;
    float f74;
    uint32_t u78;
    float f7c;
    uint32_t u80;
    float f84;
    uint32_t u88;
    float f8c, f90, f94, f98, f9c, fa0, fa4, fa8, fac, fb0, fb4, fb8, fbc, fc0, fc4, fc8;

    void Load(uint32_t instanceID);
    void Init(uint32_t instanceID);
    void SerializeObject(void* object);
};
// ---- items of slice s00b70820 end

// @ 0x00b71480
void cTuning_b708d0::Init(uint32_t instanceID)
{
    Load(instanceID ? instanceID : 0xf71fa311u);
}
