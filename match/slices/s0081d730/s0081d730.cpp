// Cast (0x0081d730): return this when the type ID is one of 0xee3f516e, 0x01539df8, 0x2f009dd0, else null.
#include "game/types.h"

struct Object_81d730 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x0081d730
void* Object_81d730::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    if (typeID == 0x01539df8)
        return (void*)this;
    return typeID == 0x2f009dd0 ? (void*)this : 0;
}
