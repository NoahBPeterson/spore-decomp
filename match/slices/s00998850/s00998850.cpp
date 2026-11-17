// Cast (0x00998850): return this when the type ID is one of 0x2fbf2058, 0xee3f516e, else null.
#include "game/types.h"

struct Object_998850 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00998850
void* Object_998850::Cast(uint32_t typeID) const
{
    if (typeID == 0x2fbf2058)
        return (void*)this;
    return typeID == 0xee3f516e ? (void*)this : 0;
}
