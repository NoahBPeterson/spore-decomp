// Cast (0x00605810): return this when the type ID is one of 0xee3f516e, 0x04c5b3ba, else null.
#include "game/types.h"

struct Object_605810 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00605810
void* Object_605810::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    return typeID == 0x04c5b3ba ? (void*)this : 0;
}
