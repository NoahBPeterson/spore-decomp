// Cast (0x00623240): return this when the type ID is one of 0x0344a654, 0xee3f516e, else null.
#include "game/types.h"

struct Object_623240 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00623240
void* Object_623240::Cast(uint32_t typeID) const
{
    if (typeID == 0x0344a654)
        return (void*)this;
    return typeID == 0xee3f516e ? (void*)this : 0;
}
