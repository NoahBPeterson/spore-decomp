// Cast (0x0098f6e0): return this when the type ID is one of 0xd02afc2b, 0xee3f516e, 0xeec58382, else null.
#include "game/types.h"

struct Object_98f6e0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x0098f6e0
void* Object_98f6e0::Cast(uint32_t typeID) const
{
    if (typeID == 0xd02afc2b)
        return (void*)this;
    if (typeID == 0xee3f516e)
        return (void*)this;
    return typeID == 0xeec58382 ? (void*)this : 0;
}
