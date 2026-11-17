// Cast (0x01053670): return this when the type ID is one of 0xee3f516e, 0x024a4ac5, 0x061d959a, else null.
#include "game/types.h"

struct Object_1053670 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x01053670
void* Object_1053670::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    if (typeID == 0x024a4ac5)
        return (void*)this;
    return typeID == 0x061d959a ? (void*)this : 0;
}
