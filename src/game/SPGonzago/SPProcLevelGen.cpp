// src/game/SPGonzago/SPProcLevelGen.cpp -- migrated from slice(s) s006237d0 by tools/migrate/rewrite.py
// Object file: SPGonzago/SPProcLevelGen.obj.  Function bodies keep the slice's code; types, members and virtual calls use the
// canonical headers under src/game/include.  Each function keeps its '// @ 0xVA' marker.

#include "game/types.h"
#include "SP/cPropertyList.h"

// ---- items of slice s006237d0 begin (TODO(rewrite): local stubs, replace by canonical classes)
namespace SP {
namespace Pollen {
struct IPropListener {
    virtual void pv0();
    virtual void OnPropertiesLoaded(SP::cPropertyList* properties);
    unsigned int pad;
    IPropListener* mpNext;
};
}
}
namespace SP {
namespace Pollen {
struct PropChangeNotifier {
    IPropListener* mpFirst;
    unsigned int mnVersion;
    bool Notify(SP::cPropertyList* properties);
};
}
}
// ---- items of slice s006237d0 end

// @ 0x006237d0
namespace SP { namespace Pollen {
bool PropChangeNotifier::Notify(SP::cPropertyList* properties)
{
    if (mnVersion != 0xffffffffU)
        return false;

    unsigned int parentCount = properties->mParent
        ? properties->mParent->GetModificationCount() : 0;
    unsigned int version = properties->mModificationCount + parentCount;
    bool changed = version != 0xffffffffU;
    if (changed) {
        mnVersion = version;
        for (IPropListener* listener = mpFirst; listener; listener = listener->mpNext)
            listener->OnPropertiesLoaded(properties);
    }
    return changed;
}
}}  // namespace SP::Pollen
