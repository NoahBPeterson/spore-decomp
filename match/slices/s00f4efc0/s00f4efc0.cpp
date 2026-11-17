// Cast (0x00f4efc0): return this when the type ID is one of 0x029da727, 0x0530a14b, else null.
#include "game/types.h"

struct Object_f4efc0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00f4efc0
void* Object_f4efc0::Cast(uint32_t typeID) const
{
    if (typeID == 0x029da727)
        return (void*)this;
    return typeID == 0x0530a14b ? (void*)this : 0;
}
