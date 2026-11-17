// Cast (0x00e492b0): return this for interface 0x355941b9, else null.
#include "game/types.h"

struct Object_e492b0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00e492b0
void* Object_e492b0::Cast(uint32_t typeID) const
{
    return typeID == 0x355941b9 ? (void*)this : 0;
}
