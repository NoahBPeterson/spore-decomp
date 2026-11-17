// Cast (0x00df5ed0): return this for interface 0x037ac490, else null.
#include "game/types.h"

struct Object_df5ed0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00df5ed0
void* Object_df5ed0::Cast(uint32_t typeID) const
{
    return typeID == 0x037ac490 ? (void*)this : 0;
}
