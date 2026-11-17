// Cast (0x005dbf60): return this when the type ID is one of 0xee3f516e, 0x2f009dd0, else null.
#include "game/types.h"

struct Object_5dbf60 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x005dbf60
void* Object_5dbf60::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    return typeID == 0x2f009dd0 ? (void*)this : 0;
}
