// Cast (0x01002dd0): return this for interface 0xee3f516e, else null.
#include "game/types.h"

struct Object_1002dd0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x01002dd0
void* Object_1002dd0::Cast(uint32_t typeID) const
{
    return typeID == 0xee3f516e ? (void*)this : 0;
}
