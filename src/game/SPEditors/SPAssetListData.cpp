// src/game/SPEditors/SPAssetListData.cpp -- migrated from slice(s) s004bafc0 by tools/migrate/rewrite.py
// Object file: SPEditors/SPAssetListData.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"

// @ 0x004bbe20
bool IsBakeableType(uint32_t type, uint8_t useSpecial)
{
    if (useSpecial && type == 0x366a930d)
        return true;
    switch (type) {
    case 0x3d97a8e4:
    case 0x2399be55:
    case 0x24682294:
    case 0x2b978c46:
    case 0x438f6347:
    case 0x476a98c7:
        return true;
    default:
        return false;
    }
}
