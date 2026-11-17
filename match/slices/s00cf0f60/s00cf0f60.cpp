// Cast (0x00cf0f60): return this for interface 0x02def34f, else null.
#include "game/types.h"

struct Object_cf0f60 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00cf0f60
void* Object_cf0f60::Cast(uint32_t typeID) const
{
    return typeID == 0x02def34f ? (void*)this : 0;
}
