// Cast (0x01052f50): return this when the type ID is one of 0xee3f516e, 0x024a4ac5, 0x060079de, else null.
#include "game/types.h"

struct Object_1052f50 {
    void* Cast(uint32_t typeID) const;
};

// @ 0x01052f50
void* Object_1052f50::Cast(uint32_t typeID) const
{
    if (typeID == 0xee3f516e)
        return (void*)this;
    if (typeID == 0x024a4ac5)
        return (void*)this;
    return typeID == 0x060079de ? (void*)this : 0;
}
