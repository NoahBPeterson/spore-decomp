// Cast (0x005a2050): return this for interface 0x029da727, else null.
#include "game/types.h"

struct Object_5a2050 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x005a2050
void* Object_5a2050::Cast(uint32_t typeID) const
{
    return typeID == 0x029da727 ? (void*)this : 0;
}
