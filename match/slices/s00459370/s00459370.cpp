// @ 0x459370  SP::CapabilityManager::GetPropIDForAbility
// PARTIAL: the original is a ~4.8 KB nested integer decision tree mapping an ability
// ResourceID (+ per-level modifier) to a property-ID hash constant.  This skeleton keeps
// the slice compiling; the decision tree is not reproduced.
#include "types.h"

unsigned int GetPropIDForAbility(unsigned int abilityID, int level)
{
    (void)abilityID;
    (void)level;
    return 0;
}
