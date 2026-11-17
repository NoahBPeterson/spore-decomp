// Cast (0x00689680): return this when the type ID is one of 0xcb90253a, 0xee3f516e, else null.
#include "game/types.h"

struct Object_689680 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00689680
void* Object_689680::Cast(uint32_t typeID) const
{
    if (typeID == 0xcb90253a)
        return (void*)this;
    return typeID == 0xee3f516e ? (void*)this : 0;
}
