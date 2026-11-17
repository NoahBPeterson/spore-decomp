// Cast (0x00dde3e0): return this when the type ID is one of 0x07ba65f3, 0xee3f516e, else null.
#include "game/types.h"

struct Object_dde3e0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00dde3e0
void* Object_dde3e0::Cast(uint32_t typeID) const
{
    if (typeID == 0x07ba65f3)
        return (void*)this;
    return typeID == 0xee3f516e ? (void*)this : 0;
}
