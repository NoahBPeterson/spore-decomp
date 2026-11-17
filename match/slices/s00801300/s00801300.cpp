// Cast (0x00801300): return this for interface 0xf121293a, else null.
#include "game/types.h"

struct Object_801300 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00801300
void* Object_801300::Cast(uint32_t typeID) const
{
    return typeID == 0xf121293a ? (void*)this : 0;
}
