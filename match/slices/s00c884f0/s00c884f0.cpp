// Cast (0x00c884f0): return this when the type ID is one of 0x01186577, 0x07bbc4ff, else null.
#include "game/types.h"

struct Object_c884f0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00c884f0
void* Object_c884f0::Cast(uint32_t typeID) const
{
    if (typeID == 0x01186577)
        return (void*)this;
    return typeID == 0x07bbc4ff ? (void*)this : 0;
}
