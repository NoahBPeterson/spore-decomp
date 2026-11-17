// Cast (0x00997d20): return this when the type ID is one of 0xee3f516e, 0xf074e1c8, else null.
#include "game/types.h"

struct Object_997d20 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00997d20
void* Object_997d20::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    return typeID == 0xf074e1c8 ? (void*)this : 0;
}
