// Cast (0x00923410): return this when the type ID is one of 0x2e9e0f1a, 0x2e9e25fe, 0xee3f516e, else null.
#include "game/types.h"

struct Object_923410 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00923410
void* Object_923410::Cast(uint32_t typeID) const
{
    if (typeID == 0x2e9e0f1a)
        return (void*)this;
    if (typeID == 0x2e9e25fe)
        return (void*)this;
    return typeID == 0xee3f516e ? (void*)this : 0;
}
