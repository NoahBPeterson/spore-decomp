// Cast (0x00c7d050): return this for interface 0x07b3a16f, else null.
#include "game/types.h"

struct Object_c7d050 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c7d050
void* Object_c7d050::Cast(uint32_t typeID) const
{
    return typeID == 0x07b3a16f ? (void*)this : 0;
}
