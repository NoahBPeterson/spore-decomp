// Cast (0x00951460): return this when the type ID is one of 0x03852c99, 0xee3f516e, 0xeec58382, else null.
#include "game/types.h"

struct Object_951460 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00951460
void* Object_951460::Cast(uint32_t typeID) const
{
    if (typeID == 0x03852c99)
        return (void*)this;
    if (typeID == 0xee3f516e)
        return (void*)this;
    return typeID == 0xeec58382 ? (void*)this : 0;
}
