// Cast (0x00dd5920): return this when the type ID is one of 0xee3f516e, 0x02ba423e, 0x2f009dd0, else null.
#include "game/types.h"

struct Object_dd5920 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00dd5920
void* Object_dd5920::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    if (typeID == 0x02ba423e)
        return (void*)this;
    return typeID == 0x2f009dd0 ? (void*)this : 0;
}
