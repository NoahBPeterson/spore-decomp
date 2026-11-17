// Cast (0x00689640): return this when the type ID is one of 0x4b99446a, 0xee3f516e, else null.
#include "game/types.h"

struct Object_689640 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00689640
void* Object_689640::Cast(uint32_t typeID) const
{
    if (typeID == 0x4b99446a)
        return (void*)this;
    return typeID == 0xee3f516e ? (void*)this : 0;
}
