// Cast (0x00e06750): return this for interface 0x046e8d1b, else null.
#include "game/types.h"

struct Object_e06750 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00e06750
void* Object_e06750::Cast(uint32_t typeID) const
{
    return typeID == 0x046e8d1b ? (void*)this : 0;
}
