// Cast (0x00ea1020): return this when the type ID is one of 0x2f009dd0, 0xee3f516e, else null.
#include "game/types.h"

struct Object_ea1020 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00ea1020
void* Object_ea1020::Cast(uint32_t typeID) const
{
    if (typeID == 0x2f009dd0)
        return (void*)this;
    return typeID == 0xee3f516e ? (void*)this : 0;
}
