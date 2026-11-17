// Cast (0x00cee250): return this for interface 0x0135b1e8, else null.
#include "game/types.h"

struct Object_cee250 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00cee250
void* Object_cee250::Cast(uint32_t typeID) const
{
    return typeID == 0x0135b1e8 ? (void*)this : 0;
}
