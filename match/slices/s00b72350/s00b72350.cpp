// Cast (0x00b72350): return this for interface 0x03d19f05, else null.
#include "game/types.h"

struct Object_b72350 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00b72350
void* Object_b72350::Cast(uint32_t typeID) const
{
    return typeID == 0x03d19f05 ? (void*)this : 0;
}
