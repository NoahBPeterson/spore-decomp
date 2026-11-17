// Cast (0x0082a020): return this when the type ID is one of 0x04a61af2, 0x2f009dd0, else null.
#include "game/types.h"

struct Object_82a020 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x0082a020
void* Object_82a020::Cast(uint32_t typeID) const
{
    if (typeID == 0x04a61af2)
        return (void*)this;
    return typeID == 0x2f009dd0 ? (void*)this : 0;
}
