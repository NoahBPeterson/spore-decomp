// Cast (0x00f31c00): return this for interface 0xb6b1576f, else null.
#include "game/types.h"

struct Object_f31c00 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00f31c00
void* Object_f31c00::Cast(uint32_t typeID) const
{
    return typeID == 0xb6b1576f ? (void*)this : 0;
}
