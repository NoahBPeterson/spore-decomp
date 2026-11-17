// Cast (0x00aff210): return this when the type ID is one of 0xee3f516e, 0x0179c807, 0x0581147f, else null.
#include "game/types.h"

struct Object_aff210 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00aff210
void* Object_aff210::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    if (typeID == 0x0179c807)
        return (void*)this;
    return typeID == 0x0581147f ? (void*)this : 0;
}
