// Cast (0x008087a0): return this when the type ID is one of 0x04a61af0, 0xee3f516e, else null.
#include "game/types.h"

struct Object_8087a0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x008087a0
void* Object_8087a0::Cast(uint32_t typeID) const
{
    if (typeID == 0x04a61af0)
        return (void*)this;
    return typeID == 0xee3f516e ? (void*)this : 0;
}
