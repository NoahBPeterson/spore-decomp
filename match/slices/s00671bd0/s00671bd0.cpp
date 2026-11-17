// Cast (0x00671bd0): return this when the type ID is one of 0xd493718f, 0xee3f516e, 0x2f009dd0, else null.
#include "game/types.h"

struct Object_671bd0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00671bd0
void* Object_671bd0::Cast(uint32_t typeID) const
{
    if (typeID == 0xd493718f)
        return (void*)this;
    if (typeID == 0xee3f516e)
        return (void*)this;
    return typeID == 0x2f009dd0 ? (void*)this : 0;
}
