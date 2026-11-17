// Cast (0x00999760): return this when the type ID is one of 0x8f6ad1c8, 0xee3f516e, else null.
#include "game/types.h"

struct Object_999760 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00999760
void* Object_999760::Cast(uint32_t typeID) const
{
    if (typeID == 0x8f6ad1c8)
        return (void*)this;
    return typeID == 0xee3f516e ? (void*)this : 0;
}
