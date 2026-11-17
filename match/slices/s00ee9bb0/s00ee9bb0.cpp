// Cast (0x00ee9bb0): return this when the type ID is one of 0xee3f516e, 0x2f009dd0, 0x568dd0ab, else null.
#include "game/types.h"

struct Object_ee9bb0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00ee9bb0
void* Object_ee9bb0::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    if (typeID == 0x2f009dd0)
        return (void*)this;
    return typeID == 0x568dd0ab ? (void*)this : 0;
}
