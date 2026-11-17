// Cast (0x00bb9c70): return this when the type ID is one of 0x03e4353b, 0x0179c807, else null.
#include "game/types.h"

struct Object_bb9c70 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00bb9c70
void* Object_bb9c70::Cast(uint32_t typeID) const
{
    if (typeID == 0x03e4353b)
        return (void*)this;
    return typeID == 0x0179c807 ? (void*)this : 0;
}
