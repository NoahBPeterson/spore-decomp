// Cast (0x00997b40): return this when the type ID is one of 0x4fc56322, 0xee3f516e, else null.
#include "game/types.h"

struct Object_997b40 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00997b40
void* Object_997b40::Cast(uint32_t typeID) const
{
    if (typeID == 0x4fc56322)
        return (void*)this;
    return typeID == 0xee3f516e ? (void*)this : 0;
}
