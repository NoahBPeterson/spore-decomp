// Cast (0x010170b0): return this when the type ID is one of 0x303154cd, 0x029da727, 0x303154cb, else null.
#include "game/types.h"

struct Object_10170b0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x010170b0
void* Object_10170b0::Cast(uint32_t typeID) const
{
    if (typeID == 0x303154cd)
        return (void*)this;
    if (typeID == 0x029da727)
        return (void*)this;
    return typeID == 0x303154cb ? (void*)this : 0;
}
