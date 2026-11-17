// Cast (0x0059a190): return this when the type ID is one of 0xee3f516e, 0x0760b41c, 0x2f009dd0, else null.
#include "game/types.h"

struct Object_59a190 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x0059a190
void* Object_59a190::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    if (typeID == 0x0760b41c)
        return (void*)this;
    return typeID == 0x2f009dd0 ? (void*)this : 0;
}
