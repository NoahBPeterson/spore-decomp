// Cast (0x00eb2f20): return this when the type ID is one of 0x07ba6612, 0xee3f516e, else null.
#include "game/types.h"

struct Object_eb2f20 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00eb2f20
void* Object_eb2f20::Cast(uint32_t typeID) const
{
    if (typeID == 0x07ba6612)
        return (void*)this;
    return typeID == 0xee3f516e ? (void*)this : 0;
}
