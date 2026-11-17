// Cast (0x0069d2d0): return this when the type ID is one of 0xee3f516e, 0x019da51a, else null.
#include "game/types.h"

struct Object_69d2d0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x0069d2d0
void* Object_69d2d0::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    return typeID == 0x019da51a ? (void*)this : 0;
}
