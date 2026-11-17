// Cast (0x00753f80): return this when the type ID is one of 0xae9cb0fa, 0xee3f516e, else null.
#include "game/types.h"

struct Object_753f80 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00753f80
void* Object_753f80::Cast(uint32_t typeID) const
{
    if (typeID == 0xae9cb0fa)
        return (void*)this;
    return typeID == 0xee3f516e ? (void*)this : 0;
}
