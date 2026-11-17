// Cast (0x005ff210): return this when the type ID is one of 0x043c974d, 0x2f009dd0, else null.
#include "game/types.h"

struct Object_5ff210 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x005ff210
void* Object_5ff210::Cast(uint32_t typeID) const
{
    if (typeID == 0x043c974d)
        return (void*)this;
    return typeID == 0x2f009dd0 ? (void*)this : 0;
}
