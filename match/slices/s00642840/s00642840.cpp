// Cast (0x00642840): return this when the type ID is one of 0xee3f516e, 0x33d558f3, else null.
#include "game/types.h"

struct Object_642840 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00642840
void* Object_642840::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    return typeID == 0x33d558f3 ? (void*)this : 0;
}
