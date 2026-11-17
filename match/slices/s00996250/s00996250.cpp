// Cast (0x00996250): return this when the type ID is one of 0x068ed590, 0x2f009dd0, 0xee3f516e, else null.
#include "game/types.h"

struct Object_996250 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00996250
void* Object_996250::Cast(uint32_t typeID) const
{
    if (typeID == 0x068ed590)
        return (void*)this;
    if (typeID == 0x2f009dd0)
        return (void*)this;
    return typeID == 0xee3f516e ? (void*)this : 0;
}
