// Cast (0x005ca8d0): return this when the type ID is one of 0xee3f516e, 0x2f009dd0, 0x52deed23, else null.
#include "game/types.h"

struct Object_5ca8d0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x005ca8d0
void* Object_5ca8d0::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    if (typeID == 0x2f009dd0)
        return (void*)this;
    return typeID == 0x52deed23 ? (void*)this : 0;
}
