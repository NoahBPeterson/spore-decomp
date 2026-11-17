// Cast (0x00ed4f30): return this when the type ID is one of 0x0774c96f, 0xee3f516e, else null.
#include "game/types.h"

struct Object_ed4f30 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00ed4f30
void* Object_ed4f30::Cast(uint32_t typeID) const
{
    if (typeID == 0x0774c96f)
        return (void*)this;
    return typeID == 0xee3f516e ? (void*)this : 0;
}
