// Cast (0x0066bd10): return this when the type ID is one of 0xee3f516e, 0x2f009dd0, 0x341772f1, else null.
#include "game/types.h"

struct Object_66bd10 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x0066bd10
void* Object_66bd10::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    if (typeID == 0x2f009dd0)
        return (void*)this;
    return typeID == 0x341772f1 ? (void*)this : 0;
}
