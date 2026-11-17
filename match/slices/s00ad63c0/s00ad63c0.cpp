// Cast (0x00ad63c0): return this when the type ID is one of 0xee3f516e, 0x055113d6, else null.
#include "game/types.h"

struct Object_ad63c0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00ad63c0
void* Object_ad63c0::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    return typeID == 0x055113d6 ? (void*)this : 0;
}
