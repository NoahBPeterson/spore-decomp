// Cast (0x00925090): return this when the type ID is one of 0x6e8d0051, 0xee3f516e, else null.
#include "game/types.h"

struct Object_925090 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00925090
void* Object_925090::Cast(uint32_t typeID) const
{
    if (typeID == 0x6e8d0051)
        return (void*)this;
    return typeID == 0xee3f516e ? (void*)this : 0;
}
