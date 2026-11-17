// Cast (0x00de0ac0): return this when the type ID is one of 0xee3f516e, 0xf5e905cd, else null.
#include "game/types.h"

struct Object_de0ac0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00de0ac0
void* Object_de0ac0::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    return typeID == 0xf5e905cd ? (void*)this : 0;
}
