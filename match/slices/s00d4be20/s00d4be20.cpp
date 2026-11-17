// Cast (0x00d4be20): return this when the type ID is one of 0x0558fe09, 0x0179c807, else null.
#include "game/types.h"

struct Object_d4be20 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00d4be20
void* Object_d4be20::Cast(uint32_t typeID) const
{
    if (typeID == 0x0558fe09)
        return (void*)this;
    return typeID == 0x0179c807 ? (void*)this : 0;
}
