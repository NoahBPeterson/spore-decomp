// Cast (0x00957510): return this when the type ID is one of 0x01be8ca6, 0xee3f516e, else null.
#include "game/types.h"

struct Object_957510 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00957510
void* Object_957510::Cast(uint32_t typeID) const
{
    if (typeID == 0x01be8ca6)
        return (void*)this;
    return typeID == 0xee3f516e ? (void*)this : 0;
}
