// Cast (0x00d4c980): return this when the type ID is one of 0x0609eedc, 0x0179c807, 0x0558fe09, else null.
#include "game/types.h"

struct Object_d4c980 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00d4c980
void* Object_d4c980::Cast(uint32_t typeID) const
{
    if (typeID == 0x0609eedc)
        return (void*)this;
    if (typeID == 0x0179c807)
        return (void*)this;
    return typeID == 0x0558fe09 ? (void*)this : 0;
}
