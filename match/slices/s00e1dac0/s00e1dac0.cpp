// Cast (0x00e1dac0): return this for interface 0x2f009dd0, else null.
#include "game/types.h"

struct Object_e1dac0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00e1dac0
void* Object_e1dac0::Cast(uint32_t typeID) const
{
    return typeID == 0x2f009dd0 ? (void*)this : 0;
}
