// Cast (0x005e0cc0): return this when the type ID is one of 0xee3f516e, 0x04c5b3ba, 0x06309608, else null.
#include "game/types.h"

struct Object_5e0cc0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x005e0cc0
void* Object_5e0cc0::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    if (typeID == 0x04c5b3ba)
        return (void*)this;
    return typeID == 0x06309608 ? (void*)this : 0;
}
