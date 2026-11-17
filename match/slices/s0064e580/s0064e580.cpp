// Cast (0x0064e580): return this when the type ID is one of 0xd3cc3400, 0xee3f516e, 0x2f009dd0, else null.
#include "game/types.h"

struct Object_64e580 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x0064e580
void* Object_64e580::Cast(uint32_t typeID) const
{
    if (typeID == 0xd3cc3400)
        return (void*)this;
    if (typeID == 0xee3f516e)
        return (void*)this;
    return typeID == 0x2f009dd0 ? (void*)this : 0;
}
