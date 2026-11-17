// Cast (0x005a88d0): return this when the type ID is one of 0xee3f516e, 0x050a1fe5, 0x050a205b, else null.
#include "game/types.h"

struct Object_5a88d0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x005a88d0
void* Object_5a88d0::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    if (typeID == 0x050a1fe5)
        return (void*)this;
    return typeID == 0x050a205b ? (void*)this : 0;
}
