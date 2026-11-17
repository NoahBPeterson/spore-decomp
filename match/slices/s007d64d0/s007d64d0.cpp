// Cast (0x007d64d0): return this for interface 0x032f9668, else null.
#include "game/types.h"

struct Object_7d64d0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x007d64d0
void* Object_7d64d0::Cast(uint32_t typeID) const
{
    return typeID == 0x032f9668 ? (void*)this : 0;
}
