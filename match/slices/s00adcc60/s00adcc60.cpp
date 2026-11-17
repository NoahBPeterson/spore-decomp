// Cast (0x00adcc60): return this when the type ID is one of 0xee3f516e, 0x0477e049, 0x0583a1cf, else null.
#include "game/types.h"

struct Object_adcc60 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00adcc60
void* Object_adcc60::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    if (typeID == 0x0477e049)
        return (void*)this;
    return typeID == 0x0583a1cf ? (void*)this : 0;
}
