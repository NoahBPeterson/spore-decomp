// Cast (0x00b2a280): return this for interface 0x0180603b, else null.
#include "game/types.h"

struct Object_b2a280 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00b2a280
void* Object_b2a280::Cast(uint32_t typeID) const
{
    return typeID == 0x0180603b ? (void*)this : 0;
}
