// Cast (0x005a4180): return this when the type ID is one of 0xee3f516e, 0x03b26ca5, 0x2f009dd0, else null.
#include "game/types.h"

struct Object_5a4180 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x005a4180
void* Object_5a4180::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    if (typeID == 0x03b26ca5)
        return (void*)this;
    return typeID == 0x2f009dd0 ? (void*)this : 0;
}
