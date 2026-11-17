// Cast (0x00951580): return this when the type ID is one of 0x03852ca0, 0xee3f516e, 0xeec58382, else null.
#include "game/types.h"

struct Object_951580 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00951580
void* Object_951580::Cast(uint32_t typeID) const
{
    if (typeID == 0x03852ca0)
        return (void*)this;
    if (typeID == 0xee3f516e)
        return (void*)this;
    return typeID == 0xeec58382 ? (void*)this : 0;
}
