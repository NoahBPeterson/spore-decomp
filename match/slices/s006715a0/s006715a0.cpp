// Cast (0x006715a0): return this when the type ID is one of 0xee3f516e, 0x14a5bc54, 0x2f009dd0, else null.
#include "game/types.h"

struct Object_6715a0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x006715a0
void* Object_6715a0::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    if (typeID == 0x14a5bc54)
        return (void*)this;
    return typeID == 0x2f009dd0 ? (void*)this : 0;
}
