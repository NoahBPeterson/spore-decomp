// Cast (0x006af580): return this when the type ID is one of 0xae9cb0fa, 0xee3f516e, 0x0498d49f, else null.
#include "game/types.h"

struct Object_6af580 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x006af580
void* Object_6af580::Cast(uint32_t typeID) const
{
    if (typeID == 0xae9cb0fa)
        return (void*)this;
    if (typeID == 0xee3f516e)
        return (void*)this;
    return typeID == 0x0498d49f ? (void*)this : 0;
}
