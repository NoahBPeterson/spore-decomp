// Cast (0x00923470): return this when the type ID is one of 0x23ab223d, 0xee3f516e, else null.
#include "game/types.h"

struct Object_923470 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00923470
void* Object_923470::Cast(uint32_t typeID) const
{
    if (typeID == 0x23ab223d)
        return (void*)this;
    return typeID == 0xee3f516e ? (void*)this : 0;
}
