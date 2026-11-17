// Cast (0x00ad5650): return this when the type ID is one of 0xee3f516e, 0x0447ff9b, else null.
#include "game/types.h"

struct Object_ad5650 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00ad5650
void* Object_ad5650::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    return typeID == 0x0447ff9b ? (void*)this : 0;
}
