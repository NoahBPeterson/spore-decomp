// Cast (0x00b5ca30): return this for interface 0x021e96f4, else null.
#include "game/types.h"

struct Object_b5ca30 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00b5ca30
void* Object_b5ca30::Cast(uint32_t typeID) const
{
    return typeID == 0x021e96f4 ? (void*)this : 0;
}
