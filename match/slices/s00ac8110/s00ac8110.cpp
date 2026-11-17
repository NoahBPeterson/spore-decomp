// Cast (0x00ac8110): return this for interface 0x01f73e49, else null.
#include "game/types.h"

struct Object_ac8110 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00ac8110
void* Object_ac8110::Cast(uint32_t typeID) const
{
    return typeID == 0x01f73e49 ? (void*)this : 0;
}
