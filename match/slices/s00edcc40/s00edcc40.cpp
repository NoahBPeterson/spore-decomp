// Cast (0x00edcc40): return this when the type ID is one of 0xee3f516e, 0x07df50da, 0x2f009dd0, else null.
#include "game/types.h"

struct Object_edcc40 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00edcc40
void* Object_edcc40::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    if (typeID == 0x07df50da)
        return (void*)this;
    return typeID == 0x2f009dd0 ? (void*)this : 0;
}
