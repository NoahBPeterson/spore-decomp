// Cast (0x006663e0): return this when the type ID is one of 0xee3f516e, 0x2f009dd0, 0x73c83e4f, else null.
#include "game/types.h"

struct Object_6663e0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x006663e0
void* Object_6663e0::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    if (typeID == 0x2f009dd0)
        return (void*)this;
    return typeID == 0x73c83e4f ? (void*)this : 0;
}
