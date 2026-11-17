// Cast (0x00ba2610): return this for interface 0xf2dcc8bc, else null.
#include "game/types.h"

struct Object_ba2610 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00ba2610
void* Object_ba2610::Cast(uint32_t typeID) const
{
    return typeID == 0xf2dcc8bc ? (void*)this : 0;
}
