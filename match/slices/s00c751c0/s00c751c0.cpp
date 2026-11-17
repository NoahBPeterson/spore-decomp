// Cast (0x00c751c0): return this for interface 0xe89adf71, else null.
#include "game/types.h"

struct Object_c751c0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c751c0
void* Object_c751c0::Cast(uint32_t typeID) const
{
    return typeID == 0xe89adf71 ? (void*)this : 0;
}
