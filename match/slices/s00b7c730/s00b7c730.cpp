// Cast (0x00b7c730): return this when the type ID is one of 0xee3f516e, 0x015a2cf2, else null.
#include "game/types.h"

struct Object_b7c730 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00b7c730
void* Object_b7c730::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    return typeID == 0x015a2cf2 ? (void*)this : 0;
}
