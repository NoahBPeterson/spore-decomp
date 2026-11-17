// Cast (0x00f32b50): return this when the type ID is one of 0x073e4efe, 0x073e4f04, 0xee3f516e, else null.
#include "game/types.h"

struct Object_f32b50 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00f32b50
void* Object_f32b50::Cast(uint32_t typeID) const
{
    if (typeID == 0x073e4efe)
        return (void*)this;
    if (typeID == 0x073e4f04)
        return (void*)this;
    return typeID == 0xee3f516e ? (void*)this : 0;
}
