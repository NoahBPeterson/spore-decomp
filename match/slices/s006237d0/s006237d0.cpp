// @ 0x006237d0
#include "game/types.h"
#include "SP/cPropertyList.h"

namespace SP {
namespace Pollen {

struct IPropListener {
    virtual void pv0();
    virtual void OnPropertiesLoaded(SP::cPropertyList* properties);
    unsigned int pad;
    IPropListener* mpNext;
};

struct PropChangeNotifier {
    IPropListener* mpFirst;
    unsigned int mnVersion;
    bool Notify(SP::cPropertyList* properties);
};

// @ 0x006237d0
bool PropChangeNotifier::Notify(SP::cPropertyList* properties) {
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

} // namespace Pollen
} // namespace SP
