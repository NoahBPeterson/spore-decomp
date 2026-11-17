// Cast (0x007db930): return this when the type ID is one of 0x029da727, 0xee3f516e, else null.
#include "game/types.h"

struct Object_7db930 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x007db930
void* Object_7db930::Cast(uint32_t typeID) const
{
    if (typeID == 0x029da727)
        return (void*)this;
    return typeID == 0xee3f516e ? (void*)this : 0;
}
