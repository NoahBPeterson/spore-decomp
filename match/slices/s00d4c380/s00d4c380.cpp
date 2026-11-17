// Cast (0x00d4c380): return this when the type ID is one of 0x05599f2c, 0x0179c807, 0x0558fe09, else null.
#include "game/types.h"

struct Object_d4c380 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00d4c380
void* Object_d4c380::Cast(uint32_t typeID) const
{
    if (typeID == 0x05599f2c)
        return (void*)this;
    if (typeID == 0x0179c807)
        return (void*)this;
    return typeID == 0x0558fe09 ? (void*)this : 0;
}
