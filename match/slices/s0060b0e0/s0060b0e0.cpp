// Cast (0x0060b0e0): return this when the type ID is one of 0xee3f516e, 0x08085c57, 0x08085c7e, else null.
#include "game/types.h"

struct Object_60b0e0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x0060b0e0
void* Object_60b0e0::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    if (typeID == 0x08085c57)
        return (void*)this;
    return typeID == 0x08085c7e ? (void*)this : 0;
}
