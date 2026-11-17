// Cast (0x005e1f50): return this when the type ID is one of 0xee3f516e, 0x0497595a, 0x2f009dd0, else null.
#include "game/types.h"

struct Object_5e1f50 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x005e1f50
void* Object_5e1f50::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    if (typeID == 0x0497595a)
        return (void*)this;
    return typeID == 0x2f009dd0 ? (void*)this : 0;
}
