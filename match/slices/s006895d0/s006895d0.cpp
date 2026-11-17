// Cast (0x006895d0): return this when the type ID is one of 0x4b8c39e4, 0xee3f516e, else null.
#include "game/types.h"

struct Object_6895d0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x006895d0
void* Object_6895d0::Cast(uint32_t typeID) const
{
    if (typeID == 0x4b8c39e4)
        return (void*)this;
    return typeID == 0xee3f516e ? (void*)this : 0;
}
