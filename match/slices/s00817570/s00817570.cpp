// Cast (0x00817570): return this when the type ID is one of 0x062ef99e, 0x2f009dd0, 0xee3f516e, else null.
#include "game/types.h"

struct Object_817570 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00817570
void* Object_817570::Cast(uint32_t typeID) const
{
    if (typeID == 0x062ef99e)
        return (void*)this;
    if (typeID == 0x2f009dd0)
        return (void*)this;
    return typeID == 0xee3f516e ? (void*)this : 0;
}
