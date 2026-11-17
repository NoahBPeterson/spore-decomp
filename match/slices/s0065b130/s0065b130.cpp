// Cast (0x0065b130): return this when the type ID is one of 0xee3f516e, 0x051d1b90, 0x2f009dd0, else null.
#include "game/types.h"

struct Object_65b130 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x0065b130
void* Object_65b130::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    if (typeID == 0x051d1b90)
        return (void*)this;
    return typeID == 0x2f009dd0 ? (void*)this : 0;
}
