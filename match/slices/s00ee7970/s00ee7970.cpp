// Cast (0x00ee7970): return this for interface 0x07560402, else null.
#include "game/types.h"

struct Object_ee7970 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00ee7970
void* Object_ee7970::Cast(uint32_t typeID) const
{
    return typeID == 0x07560402 ? (void*)this : 0;
}
