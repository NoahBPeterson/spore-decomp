// Cast (0x00923380): return this when the type ID is one of 0x0e9f1ff0, 0x6e9f4237, 0xee3f516e, else null.
#include "game/types.h"

struct Object_923380 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00923380
void* Object_923380::Cast(uint32_t typeID) const
{
    if (typeID == 0x0e9f1ff0)
        return (void*)this;
    if (typeID == 0x6e9f4237)
        return (void*)this;
    return typeID == 0xee3f516e ? (void*)this : 0;
}
