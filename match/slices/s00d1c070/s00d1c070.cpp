// Cast (0x00d1c070): return this when the type ID is one of 0x0116d389, 0x0126d3d9, else null.
#include "game/types.h"

struct Object_d1c070 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00d1c070
void* Object_d1c070::Cast(uint32_t typeID) const
{
    if (typeID == 0x0116d389)
        return (void*)this;
    return typeID == 0x0126d3d9 ? (void*)this : 0;
}
