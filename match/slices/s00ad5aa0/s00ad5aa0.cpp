// Cast (0x00ad5aa0): return this when the type ID is one of 0xee3f516e, 0x0446e38f, else null.
#include "game/types.h"

struct Object_ad5aa0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00ad5aa0
void* Object_ad5aa0::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    return typeID == 0x0446e38f ? (void*)this : 0;
}
