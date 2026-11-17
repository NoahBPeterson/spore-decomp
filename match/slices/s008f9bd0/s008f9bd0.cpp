// Cast (0x008f9bd0): return this when the type ID is one of 0x023faacf, 0xee3f516e, else null.
#include "game/types.h"

struct Object_8f9bd0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x008f9bd0
void* Object_8f9bd0::Cast(uint32_t typeID) const
{
    if (typeID == 0x023faacf)
        return (void*)this;
    return typeID == 0xee3f516e ? (void*)this : 0;
}
