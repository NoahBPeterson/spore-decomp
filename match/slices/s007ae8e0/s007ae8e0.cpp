// Cast (0x007ae8e0): return this when the type ID is one of 0xae9cb0fa, 0xee3f516e, 0x0591efe2, else null.
#include "game/types.h"

struct Object_7ae8e0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x007ae8e0
void* Object_7ae8e0::Cast(uint32_t typeID) const
{
    if (typeID == 0xae9cb0fa)
        return (void*)this;
    if (typeID == 0xee3f516e)
        return (void*)this;
    return typeID == 0x0591efe2 ? (void*)this : 0;
}
