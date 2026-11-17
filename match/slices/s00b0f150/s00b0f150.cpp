// Cast (0x00b0f150): return this when the type ID is one of 0x011966ed, 0x029da727, else null.
#include "game/types.h"

struct Object_b0f150 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00b0f150
void* Object_b0f150::Cast(uint32_t typeID) const
{
    if (typeID == 0x011966ed)
        return (void*)this;
    return typeID == 0x029da727 ? (void*)this : 0;
}
