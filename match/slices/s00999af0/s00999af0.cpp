// Cast (0x00999af0): return this when the type ID is one of 0x8f6ad1c8, 0xcf6c2b18, 0xee3f516e, else null.
#include "game/types.h"

struct Object_999af0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00999af0
void* Object_999af0::Cast(uint32_t typeID) const
{
    if (typeID == 0x8f6ad1c8)
        return (void*)this;
    if (typeID == 0xcf6c2b18)
        return (void*)this;
    return typeID == 0xee3f516e ? (void*)this : 0;
}
