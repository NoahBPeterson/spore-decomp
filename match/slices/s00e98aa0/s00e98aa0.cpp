// Cast (0x00e98aa0): return this for interface 0x014b71df, else null.
#include "game/types.h"

struct Object_e98aa0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00e98aa0
void* Object_e98aa0::Cast(uint32_t typeID) const
{
    return typeID == 0x014b71df ? (void*)this : 0;
}
