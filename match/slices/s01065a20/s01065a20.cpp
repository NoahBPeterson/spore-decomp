// Cast (0x01065a20): return this when the type ID is one of 0xee3f516e, 0x0176fab4, 0x2f009dd0, else null.
#include "game/types.h"

struct Object_1065a20 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x01065a20
void* Object_1065a20::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    if (typeID == 0x0176fab4)
        return (void*)this;
    return typeID == 0x2f009dd0 ? (void*)this : 0;
}
