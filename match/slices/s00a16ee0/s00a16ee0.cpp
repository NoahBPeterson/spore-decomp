// Cast (0x00a16ee0): return this when the type ID is one of 0xee3f516e, 0x4bc808e5, else null.
#include "game/types.h"

struct Object_a16ee0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00a16ee0
void* Object_a16ee0::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    return typeID == 0x4bc808e5 ? (void*)this : 0;
}
