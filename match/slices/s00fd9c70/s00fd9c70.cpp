// Cast (0x00fd9c70): return this for interface 0x01bd0bc3, else null.
#include "game/types.h"

struct Object_fd9c70 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00fd9c70
void* Object_fd9c70::Cast(uint32_t typeID) const
{
    return typeID == 0x01bd0bc3 ? (void*)this : 0;
}
