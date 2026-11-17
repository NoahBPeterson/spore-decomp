// Cast (0x00e310e0): return this when the type ID is one of 0x2f009dd0, 0x3548411d, else null.
#include "game/types.h"

struct Object_e310e0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00e310e0
void* Object_e310e0::Cast(uint32_t typeID) const
{
    if (typeID == 0x2f009dd0)
        return (void*)this;
    return typeID == 0x3548411d ? (void*)this : 0;
}
