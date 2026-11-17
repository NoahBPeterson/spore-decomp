// Cast (0x005e4d80): return this when the type ID is one of 0xee3f516e, 0x04aa0acd, 0x04ac90b5, else null.
#include "game/types.h"

struct Object_5e4d80 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x005e4d80
void* Object_5e4d80::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    if (typeID == 0x04aa0acd)
        return (void*)this;
    return typeID == 0x04ac90b5 ? (void*)this : 0;
}
