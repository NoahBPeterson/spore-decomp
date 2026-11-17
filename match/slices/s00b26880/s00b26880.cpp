// Cast (0x00b26880): return this when the type ID is one of 0x04162ca6, 0x0179c807, else null.
#include "game/types.h"

struct Object_b26880 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00b26880
void* Object_b26880::Cast(uint32_t typeID) const
{
    if (typeID == 0x04162ca6)
        return (void*)this;
    return typeID == 0x0179c807 ? (void*)this : 0;
}
