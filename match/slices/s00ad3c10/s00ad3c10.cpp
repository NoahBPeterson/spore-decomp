// Cast (0x00ad3c10): return this when the type ID is one of 0xee3f516e, 0x0491fa87, else null.
#include "game/types.h"

struct Object_ad3c10 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00ad3c10
void* Object_ad3c10::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    return typeID == 0x0491fa87 ? (void*)this : 0;
}
