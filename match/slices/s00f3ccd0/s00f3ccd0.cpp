// Cast (0x00f3ccd0): return this when the type ID is one of 0x073e4efe, 0x0743bb11, 0xee3f516e, else null.
#include "game/types.h"

struct Object_f3ccd0 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x00f3ccd0
void* Object_f3ccd0::Cast(uint32_t typeID) const
{
    if (typeID == 0x073e4efe)
        return (void*)this;
    if (typeID == 0x0743bb11)
        return (void*)this;
    return typeID == 0xee3f516e ? (void*)this : 0;
}
