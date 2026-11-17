// Cast (0x00bc3490): return this when the type ID is one of 0x011966ed, 0x029da727, 0x04c6a8e0, else null.
#include "game/types.h"

struct Object_bc3490 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00bc3490
void* Object_bc3490::Cast(uint32_t typeID) const
{
    if (typeID == 0x011966ed)
        return (void*)this;
    if (typeID == 0x029da727)
        return (void*)this;
    return typeID == 0x04c6a8e0 ? (void*)this : 0;
}
