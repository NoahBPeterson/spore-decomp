// Cast (0x00cfe7d0): return this when the type ID is one of 0xee3f516e, 0x0179c807, 0x0447341f, else null.
#include "game/types.h"

struct Object_cfe7d0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00cfe7d0
void* Object_cfe7d0::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    if (typeID == 0x0179c807)
        return (void*)this;
    return typeID == 0x0447341f ? (void*)this : 0;
}
