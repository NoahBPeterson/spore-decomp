// Cast (0x005e4d40): return this when the type ID is one of 0xee3f516e, 0x04aa0acd, else null.
#include "game/types.h"

struct Object_5e4d40 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x005e4d40
void* Object_5e4d40::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    return typeID == 0x04aa0acd ? (void*)this : 0;
}
