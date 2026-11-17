// Cast (0x00ad72c0): return this for interface 0x0583a1cf, else null.
#include "game/types.h"

struct Object_ad72c0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00ad72c0
void* Object_ad72c0::Cast(uint32_t typeID) const
{
    return typeID == 0x0583a1cf ? (void*)this : 0;
}
