// Cast (0x00d203b0): return this when the type ID is one of 0xee3f516e, 0x02a7ecd2, else null.
#include "game/types.h"

struct Object_d203b0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00d203b0
void* Object_d203b0::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    return typeID == 0x02a7ecd2 ? (void*)this : 0;
}
