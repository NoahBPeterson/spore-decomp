// Cast (0x01016fd0): return this when the type ID is one of 0x303154cc, 0x029da727, 0x303154cb, else null.
#include "game/types.h"

struct Object_1016fd0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x01016fd0
void* Object_1016fd0::Cast(uint32_t typeID) const
{
    if (typeID == 0x303154cc)
        return (void*)this;
    if (typeID == 0x029da727)
        return (void*)this;
    return typeID == 0x303154cb ? (void*)this : 0;
}
