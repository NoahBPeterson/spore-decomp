// Cast (0x00662840): return this when the type ID is one of 0xee3f516e, 0x13c6ee37, 0x2f009dd0, else null.
#include "game/types.h"

struct Object_662840 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00662840
void* Object_662840::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    if (typeID == 0x13c6ee37)
        return (void*)this;
    return typeID == 0x2f009dd0 ? (void*)this : 0;
}
