// Cast (0x00e13080): return this when the type ID is one of 0xee3f516e, 0x2f009dd0, 0x334c6eef, else null.
#include "game/types.h"

struct Object_e13080 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00e13080
void* Object_e13080::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    if (typeID == 0x2f009dd0)
        return (void*)this;
    return typeID == 0x334c6eef ? (void*)this : 0;
}
