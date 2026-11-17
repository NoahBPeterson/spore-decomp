// Cast (0x00fd7240): return this when the type ID is one of 0x0450062a, 0x2f009dd0, else null.
#include "game/types.h"

struct Object_fd7240 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00fd7240
void* Object_fd7240::Cast(uint32_t typeID) const
{
    if (typeID == 0x0450062a)
        return (void*)this;
    return typeID == 0x2f009dd0 ? (void*)this : 0;
}
