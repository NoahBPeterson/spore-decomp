// Cast (0x005c8bc0): return this when the type ID is one of 0xee3f516e, 0x2f009dd0, 0x72deed2b, else null.
#include "game/types.h"

struct Object_5c8bc0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x005c8bc0
void* Object_5c8bc0::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    if (typeID == 0x2f009dd0)
        return (void*)this;
    return typeID == 0x72deed2b ? (void*)this : 0;
}
