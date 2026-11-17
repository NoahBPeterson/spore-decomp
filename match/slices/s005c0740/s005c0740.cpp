// Cast (0x005c0740): return this when the type ID is one of 0xee3f516e, 0xf345e898, 0x2f009dd0, else null.
#include "game/types.h"

struct Object_5c0740 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x005c0740
void* Object_5c0740::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    if (typeID == 0xf345e898)
        return (void*)this;
    return typeID == 0x2f009dd0 ? (void*)this : 0;
}
