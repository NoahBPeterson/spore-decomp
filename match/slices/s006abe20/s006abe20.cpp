// Cast (0x006abe20): return this when the type ID is one of 0x0355d6f5, 0x02269ed1, 0xee3f516e, else null.
#include "game/types.h"

struct Object_6abe20 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x006abe20
void* Object_6abe20::Cast(uint32_t typeID) const
{
    if (typeID == 0x0355d6f5)
        return (void*)this;
    if (typeID == 0x02269ed1)
        return (void*)this;
    return typeID == 0xee3f516e ? (void*)this : 0;
}
