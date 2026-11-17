// Cast (0x0068f270): return this when the type ID is one of 0xae9cb0fa, 0xee3f516e, 0x03ed41bc, else null.
#include "game/types.h"

struct Object_68f270 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x0068f270
void* Object_68f270::Cast(uint32_t typeID) const
{
    if (typeID == 0xae9cb0fa)
        return (void*)this;
    if (typeID == 0xee3f516e)
        return (void*)this;
    return typeID == 0x03ed41bc ? (void*)this : 0;
}
