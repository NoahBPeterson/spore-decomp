// Cast (0x005a6e30): return this when the type ID is one of 0xee3f516e, 0x2f009dd0, 0x3383c6ad, else null.
#include "game/types.h"

struct Object_5a6e30 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x005a6e30
void* Object_5a6e30::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    if (typeID == 0x2f009dd0)
        return (void*)this;
    return typeID == 0x3383c6ad ? (void*)this : 0;
}
