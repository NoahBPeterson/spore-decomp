// Cast (0x007e1620): return this when the type ID is one of 0x00be9741, 0xee3f516e, else null.
#include "game/types.h"

struct Object_7e1620 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x007e1620
void* Object_7e1620::Cast(uint32_t typeID) const
{
    if (typeID == 0x00be9741)
        return (void*)this;
    return typeID == 0xee3f516e ? (void*)this : 0;
}
