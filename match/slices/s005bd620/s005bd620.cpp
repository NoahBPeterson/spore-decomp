// Cast (0x005bd620): return this when the type ID is one of 0x9ed74a02, 0xee3f516e, 0xefdf6da5, else null.
#include "game/types.h"

struct Object_5bd620 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x005bd620
void* Object_5bd620::Cast(uint32_t typeID) const
{
    if (typeID == 0x9ed74a02)
        return (void*)this;
    if (typeID == 0xee3f516e)
        return (void*)this;
    return typeID == 0xefdf6da5 ? (void*)this : 0;
}
