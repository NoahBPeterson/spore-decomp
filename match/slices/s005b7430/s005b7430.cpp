// Cast (0x005b7430): return this when the type ID is one of 0xee3f516e, 0xefdf6da5, 0x5fde642e, else null.
#include "game/types.h"

struct Object_5b7430 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x005b7430
void* Object_5b7430::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    if (typeID == 0xefdf6da5)
        return (void*)this;
    return typeID == 0x5fde642e ? (void*)this : 0;
}
