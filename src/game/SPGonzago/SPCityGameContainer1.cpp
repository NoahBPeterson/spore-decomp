// src/game/SPGonzago/SPCityGameContainer1.cpp -- migrated from slice(s) s00cedff0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPCityGameContainer1.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cGameBundleContainer.h"
#include "SP/cVarListSerializer.h"

// ---- items of slice s00cedff0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
struct cGameBundleContainer_s00ce_dff0 {
    void **m_vtbl00;
    void *AsISpatialObject();  // 0x00cee2a0 (SP::cGameBundleContainer::AsISpatialObject)
};
}
// ---- items of slice s00cedff0 end

// @ 0x00cee2a0
void *SP::cGameBundleContainer_s00ce_dff0::AsISpatialObject()
{
    if (this)
        return ((void *(__thiscall *)(void *, void *))m_vtbl00[0x14 / 4])(this, (void *)0x1186577);
    return 0;
}
