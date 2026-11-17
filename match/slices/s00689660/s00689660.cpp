// Cast (0x00689660): return this when the type ID is one of 0x0b903cc3, 0xee3f516e, else null.
#include "game/types.h"

struct Object_689660 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00689660
void* Object_689660::Cast(uint32_t typeID) const
{
    if (typeID == 0x0b903cc3)
        return (void*)this;
    return typeID == 0xee3f516e ? (void*)this : 0;
}
