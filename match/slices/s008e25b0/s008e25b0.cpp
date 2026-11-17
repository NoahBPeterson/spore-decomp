// Cast (0x008e25b0): return this when the type ID is one of 0x02b29464, 0xee3f516e, else null.
#include "game/types.h"

struct Object_8e25b0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x008e25b0
void* Object_8e25b0::Cast(uint32_t typeID) const
{
    if (typeID == 0x02b29464)
        return (void*)this;
    return typeID == 0xee3f516e ? (void*)this : 0;
}
