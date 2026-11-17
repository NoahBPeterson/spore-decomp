// Cast (0x0081d760): return this when the type ID is one of 0xee3f516e, 0x0153c9ef, else null.
#include "game/types.h"

struct Object_81d760 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x0081d760
void* Object_81d760::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    return typeID == 0x0153c9ef ? (void*)this : 0;
}
