// Cast (0x00eb1be0): return this when the type ID is one of 0x04f67fb5, 0x02269ed1, 0xee3f516e, else null.
#include "game/types.h"

struct Object_eb1be0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00eb1be0
void* Object_eb1be0::Cast(uint32_t typeID) const
{
    if (typeID == 0x04f67fb5)
        return (void*)this;
    if (typeID == 0x02269ed1)
        return (void*)this;
    return typeID == 0xee3f516e ? (void*)this : 0;
}
