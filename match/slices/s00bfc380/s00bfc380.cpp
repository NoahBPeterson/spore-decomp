// Cast (0x00bfc380): return this for interface 0x013f94d4, else null.
#include "game/types.h"

struct Object_bfc380 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00bfc380
void* Object_bfc380::Cast(uint32_t typeID) const
{
    return typeID == 0x013f94d4 ? (void*)this : 0;
}
