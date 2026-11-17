// Cast (0x005e88f0): return this when the type ID is one of 0xee3f516e, 0x04aa3b42, 0x04c5b3ba, else null.
#include "game/types.h"

struct Object_5e88f0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x005e88f0
void* Object_5e88f0::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    if (typeID == 0x04aa3b42)
        return (void*)this;
    return typeID == 0x04c5b3ba ? (void*)this : 0;
}
