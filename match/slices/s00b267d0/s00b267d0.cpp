// Cast (0x00b267d0): return this for interface 0x037e958b, else null.
#include "game/types.h"

struct Object_b267d0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00b267d0
void* Object_b267d0::Cast(uint32_t typeID) const
{
    return typeID == 0x037e958b ? (void*)this : 0;
}
