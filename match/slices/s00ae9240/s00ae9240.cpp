// Cast (0x00ae9240): return this when the type ID is one of 0x05760e04, 0xee3f516e, else null.
#include "game/types.h"

struct Object_ae9240 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00ae9240
void* Object_ae9240::Cast(uint32_t typeID) const
{
    if (typeID == 0x05760e04)
        return (void*)this;
    return typeID == 0xee3f516e ? (void*)this : 0;
}
