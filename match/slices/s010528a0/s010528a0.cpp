// Cast (0x010528a0): return this when the type ID is one of 0xee3f516e, 0x024a4ac5, else null.
#include "game/types.h"

struct Object_10528a0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x010528a0
void* Object_10528a0::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    return typeID == 0x024a4ac5 ? (void*)this : 0;
}
